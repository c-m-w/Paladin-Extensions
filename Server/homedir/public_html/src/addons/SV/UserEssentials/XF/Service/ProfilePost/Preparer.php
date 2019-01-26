<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\UserEssentials\XF\Service\ProfilePost;

use SV\UserEssentials\Service\Mentionable;
use SV\UserEssentials\Service\MentionableInterface;

/**
 * Extends \XF\Service\ProfilePost\Preparer
 */
class Preparer extends XFCP_Preparer implements MentionableInterface
{
    /**
     * Enable mention tracking for profile posts.
     */
    use Mentionable;

    /**
     * @var string
     */
    protected $entityKey = 'profilePost';
    /** @var bool */
    protected $autoLinkFilter = true;

    public function disableAutoLinking()
    {
        $this->autoLinkFilter = false;
    }

    /**
     * @param bool $format
     * @return \XF\Service\StructuredText\Preparer
     */
    protected function getStructuredTextPreparer($format = true)
    {
        $messagePreparer = parent::getStructuredTextPreparer($format);

        if (!$this->autoLinkFilter)
        {
            $messagePreparer->disableFilter('autolink');
        }

        return $messagePreparer;
    }
}
