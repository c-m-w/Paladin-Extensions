<?php

namespace ThemeHouse\UIX\Widget;

class SocialMediaFeed extends \XF\Widget\AbstractWidget
{
    protected $defaultOptions = [
        'platform' => '',
        'name' => '',
    ];

    public function verifyOptions(\XF\Http\Request $request, array &$options, &$error = null)
    {
        if (empty($options['platform'])) {
            $error = 'Please select a platform';
            return false;
        }

        if (empty($options['name'])) {
            $error = 'Please enter your name/unique ID for the selected platform';
            return false;
        }
        return true;
    }

    public function render()
    {
        return $this->renderer('thuix_widget_social_media_feed');
    }
}