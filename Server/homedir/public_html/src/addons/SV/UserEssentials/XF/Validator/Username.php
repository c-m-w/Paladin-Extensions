<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\UserEssentials\XF\Validator;

use XF\Util\Php;

/**
 * Extends \XF\Validator\Username
 */
class Username extends XFCP_Username
{
    /**
     * @param string      $value
     * @param string|null $errorKey
     * @return bool
     */
    public function isValid($value, &$errorKey = null)
    {
        if (!parent::isValid($value, $errorKey))
        {
            return false;
        }

        $username = $value;

        $notMatchRegex = $this->getOption('sv_ue_regex_not_match');
        if ($notMatchRegex && Php::isValidRegex($notMatchRegex))
        {
            if (preg_match($notMatchRegex, $username))
            {
                $errorKey = 'sv_ue_not_regex';

                return false;
            }
        }

        if ($this->getOption('sv_ue_check_previous'))
        {
            /** @var \SV\UserEssentials\Entity\UsernameChange $previousUsername */
            $previousUsername = $this->app->em()->findOne(
                'SV\UserEssentials:UsernameChange',
                ['from_username' => $username]
            );
            $selfUserId = $this->getOption('self_user_id');
            if (
                $previousUsername
                && (!$selfUserId || ($selfUserId != $previousUsername->user_id))
            )
            {
                $errorKey = 'sv_ue_previous';

                return false;
            }
        }

        return true;
    }

    /**
     * Sets up default options.
     */
    public function setupOptionDefaults()
    {
        parent::setupOptionDefaults();

        $options = $this->app->options();

        $this->options['sv_ue_regex_not_match'] = $options->useress_notmatchregex;
        $this->options['sv_ue_check_previous'] = $options->uncAllowPreviousNames;
    }

    /**
     * @param string $key
     * @param mixed  $value
     */
    public function setOption($key, $value)
    {
        parent::setOption($key, $value);

        if ($key === 'admin_edit')
        {
            $this->setOption('sv_ue_regex_not_match', null);
            $this->setOption('sv_ue_check_previous', false);
        }
    }

    /**
     * @param string $errorKey
     * @return \XF\Phrase|null
     */
    public function getPrintableErrorValue($errorKey)
    {
        $printableErrorValue = parent::getPrintableErrorValue($errorKey);
        if ($printableErrorValue)
        {
            return $printableErrorValue;
        }

        switch ($errorKey)
        {
            case 'sv_ue_not_regex':
                return \XF::phrase('please_enter_another_name_required_format');
            case 'sv_ue_previous':
                return \XF::phrase('sv_ue_please_enter_another_name_previous');
            default:
                return null;
        }
    }
}
