<?php

namespace ThemeHouse\Reactions\Pub\View\React;

class Listing extends \XF\Mvc\View
{
    public function renderHtml()
    {
        $this->response->header('X-Robots-Tag', 'none');
    }
}