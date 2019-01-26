<?php

namespace xenMade\LAU\XF\Template;

class Templater extends XFCP_Templater
{
    public function fnCopyright($templater, &$escape)
    {
        $copyright = parent::fnCopyright($templater, $escape);

        if(!empty(\XF::app()->config('xenMadeBrandingRemover')))
        {
            \XF::app()->offsetSet('xenMadeCopyright', true);
        }

        if(!\XF::app()->offsetExists('xenMadeCopyright'))
        {
            if(!file_exists(\XF::getRootDirectory() . '/src/addons/xenMade/xenMadeFreeCopyright.dat'))
            {
                $copyright .= ' | <a href="https://xenmade.com/" title="XenForo Add-ons" target="_blank" class="u-concealed">Add-Ons</a> by xenMade.com';
                \XF::app()->offsetSet('xenMadeCopyright', true);
            }
        }

        return $copyright;
    }
}
if(false)
{
    class XFCP_Templater extends \XF\Template\Templater {}
}