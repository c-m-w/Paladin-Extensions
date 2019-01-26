<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\WarningImprovements\XF\Pub\View\Member;

/**
 * Extends \XF\Pub\View\Member\WarnFill
 */
class WarnFill extends XFCP_WarnFill
{
    public function renderJson()
    {
        $response = parent::renderJson();

        /** @var \SV\WarningImprovements\XF\Entity\WarningDefinition $warningDefinition */
        $warningDefinition = $this->params['definition'];
        $options = \XF::app()->options();

        if ($options->sv_warningimprovements_conversation_locked)
        {
            $response['formValues']['input[name=conversation_locked]'] = true;
        }

        if (!$options->sv_warningimprovements_conversation_send_default)
        {
            $response['formValues']['input[name=start_conversation]'] = 0;
        }
/*
XF bug; https://xenforo.com/community/threads/form-filler-doesnt-work-well-with-disabler.143576
Use a template mopdification which calls $user.getWarningDefaultContentAction() instead of this:
        switch ($options->sv_warningimprovements_default_content_action)
        {
            case 'delete_content':
                $response['formValues']['input[name=content_action][value="delete"]'] = 1;
                break;
            case 'public_warning':
                $response['formValues']['input[name=content_action][value="public"]'] = 1;
                break;
            case 'none';
            default:
                $response['formValues']['input[name=content_action][value=""]'] = 1;
                break;
        }
*/
        if ($warningDefinition->sv_custom_title)
        {
            $response['formValues']['#customTitle'] = true;
        }

        return $response;
    }
}