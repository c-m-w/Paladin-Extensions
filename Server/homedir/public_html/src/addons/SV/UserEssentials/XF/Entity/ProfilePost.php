<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\UserEssentials\XF\Entity;

use SV\UserEssentials\Entity\Mentionable;
use SV\UserEssentials\Entity\MentionableInterface;

/*
 * Extends \XF\Entity\ProfilePost
 */
class ProfilePost extends XFCP_ProfilePost implements MentionableInterface
{
    /**
     * Enable mentioned user fetching for profile posts.
     */
    use Mentionable;
}
