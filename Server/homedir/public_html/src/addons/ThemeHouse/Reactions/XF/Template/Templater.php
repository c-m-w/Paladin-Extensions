<?php

namespace ThemeHouse\Reactions\XF\Template;

use XF\Mvc\Entity\Entity;

class Templater extends XFCP_Templater
{
    public function addDefaultHandlers()
    {
        parent::addDefaultHandlers();

        $this->addFunctions([
            'reacts' => 'fnReacts',
            'reaction' => 'fnReaction',
            'reaction_list' => 'fnReactionList',
            'reaction_content_list' => 'fnReactionContentList',
            'reaction_bar_position' => 'fnReactionBarPosition',
            'reaction_trigger_icon' => 'fnReactionTriggerIcon',
            'react_handler_status' => 'fnReactHandlerStatus',
            'react_handlers' => 'fnReactHandlers',
        ]);
    }

    public function fnReactionTriggerIcon($templater, &$escape)
    {
        $escape = false;
        $styleProperties = $this->getReactionStyleProperties();

        switch ($styleProperties['triggerType']) {
            case 'image_path':
                // {{ base_url(property('th_triggerValue_reactions'), false) }}
                return '<img src="' . $this->fnBaseUrl(
                    $templater,
                    $escape,
                    $styleProperties['triggerValue'],
                    false
                ) . '" class="th_reactions__trigger__image">';
            case 'glyph_class':
                return '<i class="' . $styleProperties['triggerValue'] . '" aria-hidden="true"></i>';
            case 'template':
            default:
                return $this->renderTemplate($styleProperties['triggerValue']);
        }
    }

    /**
     * @param $templater
     * @param $escape
     * @param Entity $content
     * @param $reacts
     * @param array $contentDetails
     * @param array $templateVars
     * @return string
     * @throws \Exception
     */
    public function fnReacts(
        $templater,
        &$escape,
        Entity $content,
        $reacts,
        array $contentDetails,
        $showReactLink = false,
        array $templateVars = []
    ) {
        $escape = false;

        return $this->renderTemplate('public:th_display_bar_internal_reactions', array_merge([
            'reactionList' => $this->preEscaped($this->fnReactionList(
                $templater,
                $escape,
                $content,
                $reacts,
                $contentDetails
            ), 'html'),
            'reactionContentList' => $this->preEscaped($this->fnReactionContentList(
                $templater,
                $escape,
                $content,
                $reacts,
                $contentDetails,
                $showReactLink
            ), 'html'),
        ], $templateVars));
    }

    /**
     * @param $templater
     * @param $escape
     * @param $reaction
     * @param string $class
     * @return bool|mixed
     */
    public function fnReaction(
        $templater,
        &$escape,
        $reaction,
        $class = ''
    ) {
        if (is_scalar($reaction)) {
            $reactions = $this->app->container('reactions');
            if (array_key_exists($reaction, $reactions)) {
                $reaction = $reactions[$reaction];
            } else {
                return false;
            }
        }

        $escape = false;

        /** @var \ThemeHouse\Reactions\XF\Str\Formatter $formatter */
        $formatter = $this->app->stringFormatter();
        return $formatter->getReactionHtml($reaction, $this->getReactionStyleProperties(), $class);
    }

    /**
     * @param $templater
     * @param $escape
     * @param Entity $content
     * @param $reactUsers
     * @param array $contentDetails
     * @return bool|string
     * @throws \Exception
     */
    public function fnReactionList($templater, &$escape, Entity $content, $reactUsers, array $contentDetails)
    {
        $escape = false;

        $this->processContentDetails($contentDetails);

        $visitor = \XF::visitor();
        if (!$this->fnReactHandlerStatus(
            $templater,
            $escape,
            $contentDetails['contentType']
        ) || !$visitor->user_id || $visitor->user_id == $contentDetails['contentUserId']) {
            return false;
        }

        $reactHandler = $this->getReactHandlerByEntity($content);
        $reactions = $reactHandler->buildValidReactionsList('react');

        $userReacts = [];
        $currentCount = $cannotUnreact = array();
        if (!empty($reactUsers)) {
            foreach ($reactUsers as $reactUser) {
                if ($reactUser->react_user_id == $visitor->user_id) {
                    $userReacts[] = $reactUser;
                    if (!$reactHandler->canUnreactContent($content, $reactUser)) {
                        $cannotUnreact[] = $reactUser->reaction_id;
                        continue;
                    }

                    if (array_key_exists($reactUser->reaction_id, $reactions)) {
                        $currentCount[] = $reactUser->reaction_id;
                        unset($reactions[$reactUser->reaction_id]);
                    }
                }
            }
        }

        $exceedsMax = $this->getReactedContentRepo()->checkIfCurrentMaxExceedsPermissions($visitor, $content);

        $output = [
            'userReacts' => $userReacts,
            'reactions' => false,
            'unreactLink' => false,
            'modifyReactLink' => false
        ];

        /** @var \ThemeHouse\Reactions\XF\Str\Formatter $formatter */
        $formatter = $this->app->stringFormatter();

        if (!$exceedsMax) {
            foreach ($reactions as $reactionId => $reaction) {
                if ($reaction['random'] && count($reactions) === 1) {
                    continue;
                }

                if (in_array($reactionId, $cannotUnreact)) {
                    continue;
                }

                $output['reactions'][$reaction['reaction_id']] = [
                    'url' => $reactHandler->getReactLink($contentDetails['contentId'], $reactionId),
                    'rendered' => $this->preEscaped($formatter->getReactionHtml(
                        $reaction,
                        $this->getReactionStyleProperties()
                    ), 'html'),
                    'is_default' => $reaction['is_default'],
                ];
            }
        }

        if (!$exceedsMax && count($currentCount) && !empty($output['reactions'])) {
            $output['modifyReactLink'] = $reactHandler->getModifyReactLink($contentDetails['contentId']);
        }

        if (($exceedsMax || empty($output['reactions'])) && !empty($userReacts)) {
            $output['unreactLink'] = $reactHandler->getUnreactAllLink($contentDetails['contentId']);
        }

        return $this->renderTemplate('public:th_reaction_list_reactions', $output);
    }

    /**
     * @param $templater
     * @param $escape
     * @param Entity $content
     * @param $contentReactions
     * @param array $contentDetails
     * @param bool $showReactLink
     * @param int $limit
     * @param string $class
     * @param bool $forceMinimal
     * @return bool|string
     * @throws \Exception
     */
    public function fnReactionContentList(
        $templater,
        &$escape,
        Entity $content,
        $contentReactions,
        array $contentDetails,
        $showReactLink = false,
        $limit = 3,
        $cutOff = 0,
        $class = '',
        $forceMinimal = false
    ) {
        $escape = false;

        $this->processContentDetails($contentDetails);

        if (!$this->fnReactHandlerStatus(
            $templater,
            $escape,
            $contentDetails['contentType']
        ) || empty($contentReactions)) {
            return false;
        }

        $output = [
            'reacts',
            'reactionListUrl' => (!$forceMinimal ? $this->getReactHandlerByEntity($content)->getListLink($contentDetails['contentId']) : false)
        ];

        $reactions = \XF::app()->container('reactions');

        if (empty($reactions)) {
            return false;
        }

        $reactionsCount = [];
        foreach ($contentReactions as &$contentReaction) {
            if (isset($reactionsCount[$contentReaction['reaction_id']])) {
                $reactionsCount[$contentReaction['reaction_id']] += 1;
            } else {
                $reactionsCount[$contentReaction['reaction_id']] = 1;
            }
        }

        if (empty($reactionsCount)) {
            return false;
        }

        /** @var \ThemeHouse\Reactions\XF\Str\Formatter $formatter */
        $formatter = $this->app->stringFormatter();

        foreach ($reactionsCount as $reactionId => $count) {
            if (!isset($reactions[$reactionId])) {
                continue;
            }

            $reaction = $reactions[$reactionId];
            $itemOutput = [
                'count' => $count,
                'rendered' => $this->preEscaped($formatter->getReactionHtml(
                    $reaction,
                    $this->getReactionStyleProperties(),
                    $class
                ), 'html'),
                'title' => ((count($reactionsCount) < $limit && !$forceMinimal) ? $reaction['title'] : null),
            ];

            if ($showReactLink) {
                $reactHandler = $this->getReactHandlerByEntity($content);
                $itemOutput['url'] = $reactHandler->getReactLink($contentDetails['contentId'], $reactionId);
                $itemOutput['canReact'] = $reactHandler->canReactContent($content);
            }
            $output['reacts'][] = $itemOutput;
        }

        usort($output['reacts'], function ($a, $b) {
            return $a['count'] <= $b['count'];
        });

        if ($cutOff) {
            $output['reacts'] = array_slice($output['reacts'], 0, $cutOff);
        }

        return $this->renderTemplate('public:th_reaction_content_list_reactions', $output);
    }

    /**
     * @param $templater
     * @param $escape
     * @param $contentType
     * @return bool|int|null|string
     * @throws \Exception
     */
    public function fnReactionBarPosition($templater, &$escape, $contentType)
    {
        $reactHandler = $this->getReactHandlerByType($contentType);

        if (!$reactHandler) {
            return false;
        }

        if (!$positions = $reactHandler->getReactionBarPositions()) {
            return false;
        }

        /** @var array $positions */
        $styleProperties = $this->getReactionStyleProperties();
        if (empty($styleProperties['reactionBarPositions'][$contentType])) {
            reset($positions);
            return key($positions);
        }

        return $styleProperties['reactionBarPositions'][$contentType];
    }

    /**
     * @param $templater
     * @param $escape
     * @param $contentType
     * @return bool
     * @throws \Exception
     */
    public function fnReactHandlerStatus($templater, &$escape, $contentType)
    {
        $reactHandler = $this->getReactHandlerByType($contentType);
        if (!$reactHandler) {
            return false;
        }

        return $reactHandler->getStatus();
    }

    /**
     * @param $templater
     * @param $escape
     * @return \ThemeHouse\Reactions\React\AbstractHandler[]
     * @throws \Exception
     */
    public function fnReactHandlers($templater, &$escape)
    {
        return $this->getReactHandlerRepo()->getReactHandlers();
    }

    /**
     * @param array $contentDetails
     */
    protected function processContentDetails(array &$contentDetails)
    {
        if (!count(array_filter(array_keys($contentDetails), 'is_string')) > 0) {
            $contentDetails = [
                'contentType' => $contentDetails[0],
                'contentId' => $contentDetails[1],
                'contentUserId' => (isset($contentDetails[2]) ? $contentDetails[2] : null)
            ];
        }
    }

    /**
     * @return array
     */
    protected function getReactionStyleProperties()
    {
        $style = $this->getStyle();
        if (!$style) {
            $style = \XF::app()->container('style.fallback');
        }

        return [
            'imageDimensions' => $style->getProperty('thReactionsImageDimensions'),
            'triggerType' => $style->getProperty('th_triggerType_reactions'),
            'triggerValue' => $style->getProperty('th_triggerValue_reactions'),
            'reactionBarPositions' => $style->getProperty('th_reactionBar_location_reactions')
        ];
    }


    /**
     * @return \ThemeHouse\Reactions\Repository\Reaction
     */
    protected function getReactionRepo()
    {
        /** @noinspection PhpIncompatibleReturnTypeInspection */
        return \XF::Repository('ThemeHouse\Reactions:Reaction');
    }

    /**
     * @return \ThemeHouse\Reactions\Repository\ReactedContent
     */

    protected function getReactedContentRepo()
    {
        /** @noinspection PhpIncompatibleReturnTypeInspection */
        return \XF::Repository('ThemeHouse\Reactions:ReactedContent');
    }

    /**
     * @return \ThemeHouse\Reactions\Repository\ReactHandler
     */
    protected function getReactHandlerRepo()
    {
        /** @noinspection PhpIncompatibleReturnTypeInspection */
        return \XF::Repository('ThemeHouse\Reactions:ReactHandler');
    }

    /**
     * @param $entity
     * @return \ThemeHouse\Reactions\React\AbstractHandler
     * @throws \Exception
     */
    protected function getReactHandlerByEntity(Entity $entity)
    {
        return $this->getReactHandlerRepo()->getReactHandlerByEntity($entity, false);
    }

    /**
     * @param $contentType
     * @return \ThemeHouse\Reactions\React\AbstractHandler
     * @throws \Exception
     */
    protected function getReactHandlerByType($contentType)
    {
        return $this->getReactHandlerRepo()->getReactHandlerByType($contentType, false);
    }
}
