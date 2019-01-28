<?php

namespace ForoAgency\FontAwesome\BbCode;
use XF\BbCode\Renderer\AbstractRenderer;

class FontAwesome
{
    public static function bbcode($tagChildren, $tagOption, $tag, array $options, $renderer)
    {

        if($tag['children'])
        {
            $text = '';
            foreach ($tag['children'] AS $child)
            {
                $explodedChild = @explode(' ', $child);

                if(is_array($explodedChild) || is_object($explodedChild))
                {
                    foreach ($explodedChild as $key => $value)
                    {
                            if (strpos($value, 'fa-', 0) !== 0)
                            {
                                $explodedChild[$key] = null;
                            }
                            $text .= $explodedChild[$key] . ' ';
                    }
                }

                // Fix XSS
                $text = str_replace("[", "", $text);
                $text = str_replace("]", "", $text);
                $text = addslashes($text);

                return '<i class="fa '. htmlspecialchars($text) .'"></i>';
            }
        }
	}
}
