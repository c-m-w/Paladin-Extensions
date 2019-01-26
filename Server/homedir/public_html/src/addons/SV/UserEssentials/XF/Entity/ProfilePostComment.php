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
 * Extends \XF\Entity\ProfilePostComment
 */
class ProfilePostComment extends XFCP_ProfilePostComment implements MentionableInterface
{
    /**
     * Enable mentioned user fetching for profile post comments.
     */
    use Mentionable;
}
