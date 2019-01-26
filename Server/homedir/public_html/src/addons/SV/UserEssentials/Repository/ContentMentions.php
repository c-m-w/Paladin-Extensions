<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\UserEssentials\Repository;

use XF\Mvc\Entity\Repository;

use SV\UserEssentials\Entity\MentionableInterface as EntityMentionableInterface;

/**
 * A repository for content mention entities.
 */
class ContentMentions extends Repository
{
    /**
     * @return array
     */
    public function getMentionTypes()
    {
        return [
            'm'   => 'XF:User',
            'mg'  => 'XF:UserGroup',
            'mgu' => 'XF:User',
            'q'   => 'XF:User'
        ];
    }

    /**
     * @return array
     */
    public function getSupportedContentTypes()
    {
        return [
          'post' => [
                'format'   => 'bbcode',
                'preparer' => 'XF:Post\Preparer',
                'getMessage' => function ($entity) {
                    /** @var \XF\Entity\Post $entity */
                    return $entity->message;
                },
                'setMessage' => function ($preparer, $message) {
                    /** @var \SV\UserEssentials\XF\Service\Post\Preparer $preparer */
                    $preparer->disableAutoLinking();
                    $preparer->setMessage($message, true, false);
                },
          ],
          'profile_post' => [
                'format'   => 'structured',
                'preparer' => 'XF:ProfilePost\Preparer',
                'getMessage' => function ($entity) {
                    /** @var \XF\Entity\ProfilePost $entity */
                    return $entity->message;
                },
                'setMessage' => function ($preparer, $message) {
                    /** @var \SV\UserEssentials\XF\Service\ProfilePost\Preparer $preparer */
                    $preparer->disableAutoLinking();
                    $preparer->setMessage($message);
                },
          ],
          'profile_post_comment' => [
                'format'   => 'structured',
                'preparer' => 'XF:ProfilePostComment\Preparer',
                'getMessage' => function ($entity) {
                    /** @var \XF\Entity\ProfilePostComment $entity */
                    return $entity->message;
                },
                'setMessage' => function ($preparer, $message) {
                    /** @var \SV\UserEssentials\XF\Service\ProfilePostComment\Preparer $preparer */
                    $preparer->disableAutoLinking();
                    $preparer->setMessage($message);
                },
          ]
        ];
    }


    /**
     * @param string $contentType
     * @param array  $with
     * @return array
     */
    public function getContentTypeWith($contentType, $with = [])
    {
        $with[] = 'User';
        $with[] = 'Mentions';

        switch($contentType)
        {
            case 'post':
                $with[] = 'Thread';
                $with[] = 'Thread.Forum';
                break;
        }
        return $with;
    }

    /**
     * @return array
     */
    public function getSupportedContentTypePhrases($plural = false)
    {
        return array_intersect_key(
            \XF::app()->getContentTypePhrases($plural),
            $this->getSupportedContentTypes()
        );
    }

    /**
     * @param string                                     $type
     * @param array|\XF\Mvc\Entity\AbstractCollection ...$collections
     *
     * @return array
     *
     * @throws \InvalidArgumentException If an invalid mention type is provided
     * @throws \InvalidArgumentException If a collection contains a non-mentionable entity
     */
    public function getMentionIds($type, ...$collections)
    {
        $mentionTypes = $this->getMentionTypes();
        if (!isset($mentionTypes[$type])) {
            throw new \InvalidArgumentException("Invalid mention type: {$type}");
        }

        $ids = [];
        foreach ($collections as $collection) {
            /** @var \XF\Mvc\Entity\AbstractCollection $collection */
            foreach ($collection as $entity) {
                if (!($entity instanceof EntityMentionableInterface)) {
                    $rootClass = \XF::extension()->resolveExtendedClassToRoot(
                        $entity
                    );
                    throw new \InvalidArgumentException(
                        "Entity must implement MentionableInterface ({$rootClass}), make sure the SV/UserEssentials add-on is enabled"
                    );
                }

                /** @var EntityMentionableInterface $entity */
                $mentions = $entity->getContentMentions(false);
                if ($mentions)
                {
                    $ids[] = $mentions->getIds($type);
                }
            }
        }

        return $ids ? array_unique(array_merge(...$ids)) : [];
    }

    /**
     * @param string                                     $type
     * @param array|\XF\Mvc\Entity\AbstractCollection ...$collections
     *
     * @return \XF\Mvc\Entity\AbstractCollection
     *
     * @throws \InvalidArgumentException If an invalid mention type is provided
     */
    public function getMentionEntities($type, ...$collections)
    {
        $mentionTypes = $this->getMentionTypes();
        if (!isset($mentionTypes[$type])) {
            throw new \InvalidArgumentException("Invalid mention type: {$type}");
        }

        $ids = $this->getMentionIds($type, ...$collections);
        return $this->em->findByIds($mentionTypes[$type], $ids);
    }

    /**
     * @param string $contentType
     * @param int    $contentId
     */
    public function rebuildContentMentions($contentType, $contentId)
    {
        /** @var \XF\Mvc\Entity\Entity $entity */
        $entity = \XF::app()->findByContentType($contentType, $contentId, $this->getContentTypeWith($contentType, ['User']));

        if (!($entity instanceof EntityMentionableInterface))
        {
            $rootClass = \XF::extension()->resolveExtendedClassToRoot($entity);
            throw new \InvalidArgumentException(
                "Entity must implement MentionableInterface ({$rootClass}), make sure the SV/UserEssentials add-on is enabled"
            );
        }
        if (!$entity->isValidRelation('User'))
        {
            $rootClass = \XF::extension()->resolveExtendedClassToRoot($entity);
            throw new \InvalidArgumentException(
                "Entity must have a User relation ({$rootClass}), make sure the SV/UserEssentials add-on is enabled"
            );
        }

        /** @var \XF\Repository\User $userRepo */
        $userRepo = $this->repository('XF:User');
        $user = $entity->getRelation('User');
        $user = $user ? $user : $userRepo->getGuestUser();

        \XF::asVisitor($user, function () use ($entity, $contentType, $contentId) {
            $db = $this->db();

            $options = \XF::options();
            $urlToPageTitle = $options->urlToPageTitle['enabled'];
            $autoEmbedMedia = $options->autoEmbedMedia;
            $options->urlToPageTitle['enabled'] = false;
            $options->autoEmbedMedia['embedType'] = 0;
            try
            {
                $db->beginTransaction();

                $preparer = $this->getContentPreparer($contentType, $entity);
                $mentions = $entity->addContentMentions($preparer);

                if ($mentions && $mentions->exists() && !$mentions->mention_ids)
                {
                    $mentions->reset();
                    $mentions->delete();
                }
                $db->commit();
            }
            catch (\Exception $e)
            {
                \XF::logException($e, true, "Error parsing {$contentType} - {$contentId} :", true);
                throw $e;
            }
            finally
            {
                $options->urlToPageTitle['enabled'] = $urlToPageTitle;
                $options->autoEmbedMedia = $autoEmbedMedia;
            }
        });
    }

    /**
     * @param string                $contentType
     * @param \XF\Mvc\Entity\Entity $entity
     *
     * @return \XF\Service\AbstractService
     *
     * @throws \InvalidArgumentException If content type is unsupported
     */
    protected function getContentPreparer($contentType, $entity)
    {
        $contentTypes = $this->getSupportedContentTypes();
        if (!isset($contentTypes[$contentType])) {
            throw new \InvalidArgumentException(
                "Unsupported content type: {$contentType}"
            );
        }
        $contentType = $contentTypes[$contentType];

        $getMessage = $contentType['getMessage'];
        $message = $getMessage($entity);

        /** @var \SV\UserEssentials\XF\Str\MentionFormatter $mentionFormatter */
        $mentionFormatter = \XF::app()->stringFormatter()->getMentionFormatter();
        switch ($contentType['format']) {
            case 'bbcode':
                $message = $mentionFormatter->getMentionsPlainTextFromBbCode($message);
                break;

            case 'structured':
                $message = $mentionFormatter->getMentionsPlainTextFromStructuredText($message);
                break;
            default:
                throw new \LogicException("Unknown format type");
        }

        $preparer = \XF::service($contentType['preparer'], $entity);
        $setMessage = $contentType['setMessage'];
        $setMessage($preparer, $message);
        return $preparer;
    }
}
