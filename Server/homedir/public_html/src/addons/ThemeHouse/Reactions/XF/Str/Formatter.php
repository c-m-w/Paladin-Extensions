<?php

namespace ThemeHouse\Reactions\XF\Str;

class Formatter extends XFCP_Formatter
{
    protected $reactionCache = [];

    public function getReactionHtml($reaction, $styleProperties, $class = '')
    {
        if (isset($this->reactionCache[$reaction['reaction_id']])) {
            return $this->reactionCache[$reaction['reaction_id']];
        }

        $pather = $this->smilieHtmlPather;

        $openingTag = '<span class="reaction reaction' . (empty($class) ?: ' ' . $class) . '" title="' . $reaction['title'] . '">'; $closingTag = '</span>';

        if ($reaction['styling_type'] == 'image') {
            if ($reaction['image_type'] == 'normal') {
                $url = htmlspecialchars($pather ? $pather($reaction['image_url'], 'base') : $reaction['image_url']);
                $srcSet = '';
                if (!empty($reaction['image_url_2x'])) {
                    $url2x = htmlspecialchars($pather ? $pather($reaction['image_url_2x'], 'base') : $reaction['image_url_2x']);
                    $srcSet = 'srcset="' . $url2x . ' 2x"';
                }

                $reactionCache[$reaction['reaction_id']] = $openingTag . '<img src="' . $url . '" ' . $srcSet . ' class="reaction--normal reaction--normal' . $reaction['reaction_id']
                    . '" alt="' . $reaction['title'] . '"'
                    . '/>' . $closingTag;
            }

            if ($reaction['image_type'] == 'sprite') {
                // embed a data URI to avoid a request that doesn't respect paths fully
                $url = 'data:image/gif;base64,R0lGODlhAQABAAAAACH5BAEKAAEALAAAAAABAAEAAAICTAEAOw==';
                $reactionCache[$reaction['reaction_id']] = $openingTag . '<img src="' . $url . '" class="reaction--sprite reaction--sprite' . $reaction['reaction_id']
                    . '" alt="' . $reaction['title'] . '" />' . $closingTag;
            }
        }

        if ($reaction['styling_type'] == 'text') {
            $reactionCache[$reaction['reaction_id']] = $openingTag . $reaction['reaction_text'] . $closingTag;
        }

        if ($reaction['styling_type'] == 'css_class') {
            $reactionCache[$reaction['reaction_id']] = $openingTag . '<i class="' . $reaction['reaction_text'] . '"></i>' . $closingTag;
        }

        if ($reaction['styling_type'] == 'html_css') {
            $reactionCache[$reaction['reaction_id']] = $openingTag . $reaction['styling']['html_css']['html'] . $closingTag;
        }

        return $reactionCache[$reaction['reaction_id']];
    }
}
