<?php

namespace ThemeHouse\Reactions\XF\Template;

use XF\App;
use XF\Language;
use XF\Mvc\Entity\Entity;
use XF\Mvc\Entity\AbstractCollection;
use XF\Mvc\Router;
use XF\Util\Arr;

class Templater extends XFCP_Templater
{
    public function addDefaultHandlers()
    {
        parent::addDefaultHandlers();

        $this->addFunctions([
            'reacts' => 'fnReacts',
            'reaction' => 'fnReaction',
            'reaction_list' => 'fnReactionList',
            'reaction_content_list' => 'fnReactionContentList',
            'reaction_bar_position' => 'fnReactionBarPosition',
            'reaction_trigger_icon' => 'fnReactionTriggerIcon',
            'react_handler_status' => 'fnReactHandlerStatus',
            'react_handlers' => 'fnReactHandlers',
        ]);
    }

    public function fnReactionTriggerIcon($templater, &$escape)
    {
        $escape = false;
        $styleProperties = $this->getReactionStyleProperties();

        switch ($styleProperties['triggerType']) {
            case 'image_path':
                // {{ base_url(property('th_triggerValue_reactions'), false) }}
                return '<img src="' . $this->fnBaseUrl($templater, $escape, $styleProperties['triggerValue'], false) . '" class="th_reactions__trigger__image">';
            case 'glyph_class':
                return '<i class="' . $styleProperties['triggerValue'] . '" aria-hidden="true"></i>';
            case 'template':
            default:
                return $this->renderTemplate($styleProperties['triggerValue']);
        }
    }

    public function fnReacts($templater, &$escape, Entity $content, $reacts, array $contentDetails, array $templateVars = [])
    {
        $escape = false;

        return $this->renderTemplate('public:th_display_bar_internal_reactions', array_merge([
            'reactionList' => $this->preEscaped($this->fnReactionList($templater, $escape, $content, $reacts, $contentDetails), 'html'),
            'reactionContentList' => $this->preEscaped($this->fnReactionContentList($templater, $escape, $content, $reacts, $contentDetails), 'html'),
        ], $templateVars));
    }

    public function fnReaction($templater, &$escape, $reaction, $class = '', $hideDimensions = false)
    {
        if (is_scalar($reaction)) {
            $reactions = $this->app->container('reactions');
            if (array_key_exists($reaction, $reactions)) {
                $reaction = $reactions[$reaction];
            } else {
                return false;
            }
        }

        $escape = false;

        $formatter = $this->app->stringFormatter();
        return $formatter->getReactionHtml($reaction, $this->getReactionStyleProperties(), $class, $hideDimensions);
    }

    public function fnReactionList($templater, &$escape, Entity $content, $reactUsers, array $contentDetails)
    {
        $escape = false;

        $this->processContentDetails($contentDetails);

        $visitor = \XF::visitor();
        if (!$this->fnReactHandlerStatus($templater, $escape, $contentDetails['contentType']) || !$visitor->user_id || $visitor->user_id == $contentDetails['contentUserId']) {
            return false;
        }

        $reactHandler = $this->getReactHandlerByEntity($content);
        $reactions = $reactHandler->buildValidReactionsList('react');

        $userReacts = [];
        $currentCount = $cannotUnreact = array();
        if (!empty($reactUsers)) {
            foreach ($reactUsers as $reactUser) {
                if ($reactUser->react_user_id == $visitor->user_id) {
                    $userReacts[] = $reactUser;
                    if (!$reactHandler->canUnreactContent($content, $reactUser)) {
                        $cannotUnreact[] = $reactUser->reaction_id; continue;
                    }

                    if (array_key_exists($reactUser->reaction_id, $reactions)) {
                        $currentCount[] = $reactUser->reaction_id;
                        unset($reactions[$reactUser->reaction_id]);
                    }
                }
            }
        }

        $exceedsMax = $this->getReactedContentRepo()->checkIfCurrentMaxExceedsPermissions($visitor, $content);

        $output = [
            'userReacts' => $userReacts,
            'reactions' => false,
            'unreactLink' => false,
            'modifyReactLink' => false
        ];

        $formatter = $this->app->stringFormatter();

        if (!$exceedsMax) {
            foreach ($reactions as $reactionId => $reaction) {
                if ($reaction['random'] && count($reactions) === 1) {
                    continue;
                }

                if (in_array($reactionId, $cannotUnreact)) {
                    continue;
                }

                $output['reactions'][$reaction['reaction_id']] = [
                    'url' => $reactHandler->getReactLink($contentDetails['contentId'], $reactionId),
                    'rendered' => $this->preEscaped($formatter->getReactionHtml($reaction, $this->getReactionStyleProperties()), 'html')
                ];
            }
        }

        if (!$exceedsMax && count($currentCount) && !empty($output['reactions'])) {
            $output['modifyReactLink'] = $reactHandler->getModifyReactLink($contentDetails['contentId']);
        }

        if (($exceedsMax || empty($output['reactions'])) && !empty($userReacts)) {
            $output['unreactLink'] = $reactHandler->getUnreactAllLink($contentDetails['contentId']);
        }

        return $this->renderTemplate('public:th_reaction_list_reactions', $output);
    }

    public function fnReactionContentList($templater, &$escape, Entity $content, $contentReactions, array $contentDetails, $showReactLink=false, $limit = 3, $class = '', $forceMinimal = false)
    {
        $escape = false;

        $this->processContentDetails($contentDetails);

        if (!$this->fnReactHandlerStatus($templater, $escape, $contentDetails['contentType']) || empty($contentReactions)) {
            return false;
        }

        $output = [
            'reacts',
            'reactionListUrl' => (!$forceMinimal ? $this->getReactHandlerByEntity($content)->getListLink($contentDetails['contentId']) : false)
        ];

        $reactions = \XF::app()->container('reactions');

        if (empty($reactions)) {
            return false;
        }

        $reactionsCount = [];
        foreach ($contentReactions as &$contentReaction) {
            if (isset($reactionsCount[$contentReaction['reaction_id']])) {
                $reactionsCount[$contentReaction['reaction_id']] += 1;
            } else {
                $reactionsCount[$contentReaction['reaction_id']] = 1;
            }
        }

        if (empty($reactionsCount)) {
            return false;
        }

        $formatter = $this->app->stringFormatter();

        foreach ($reactionsCount as $reactionId => $count) {
            if (!isset($reactions[$reactionId])) {
                continue;
            }

            $reaction = $reactions[$reactionId];
            $itemOutput = [
                'count' => $count,
                'rendered' => $this->preEscaped($formatter->getReactionHtml($reaction, $this->getReactionStyleProperties(), $class), 'html'),
                'title' => ((count($reactionsCount) < $limit && !$forceMinimal) ? $reaction['title'] : null),
            ];

            if ($showReactLink) {
                $reactHandler = $this->getReactHandlerByEntity($content);
                $itemOutput['url'] = $reactHandler->getReactLink($contentDetails['contentId'], $reactionId);
                $itemOutput['canReact'] = $reactHandler->canReactContent($content);
            }
            $output['reacts'][] = $itemOutput;
        }

        return $this->renderTemplate('public:th_reaction_content_list_reactions', $output);
    }

    public function fnReactionBarPosition($templater, &$escape, $contentType)
    {
        if (!$positions = $this->getReactHandlerByType($contentType)->getReactionBarPositions()) {
            return false;
        }

        $styleProperties = $this->getReactionStyleProperties();
        if (empty($styleProperties['reactionBarPositions'][$contentType])) {
            reset($positions);
            return key($positions);
        }

        return $styleProperties['reactionBarPositions'][$contentType];
    }

    public function fnReactHandlerStatus($templater, &$escape, $contentType)
    {
        $reactHandler = $this->getReactHandlerByType($contentType);
        if (!$reactHandler) {
            return false;
        }

        return $reactHandler->getStatus();
    }

    public function fnReactHandlers($templater, &$escape)
    {
        return $this->getReactHandlerRepo()->getReactHandlers();
    }

    protected function processContentDetails(array &$contentDetails)
    {
        if (!count(array_filter(array_keys($contentDetails), 'is_string')) > 0) {
            $contentDetails = [
                'contentType' => $contentDetails[0],
                'contentId' => $contentDetails[1],
                'contentUserId' => (isset($contentDetails[2]) ? $contentDetails[2] : null)
            ];
        }
    }

    protected function getReactionStyleProperties()
    {
        // This should be impossible, but some add-ons are breaking people's boards.
        if (!$this->style) {
            $this->setStyle(\XF::app()->container->style);
        }

        return [
            'imageDimensions' => $this->style->getProperty('thReactionsImageDimensions'),
            'triggerType' => $this->style->getProperty('th_triggerType_reactions'),
            'triggerValue' => $this->style->getProperty('th_triggerValue_reactions'),
            'reactionBarPositions' => $this->style->getProperty('th_reactionBar_location_reactions')
        ];
    }

    protected function getReactionRepo()
    {
        return \XF::Repository('ThemeHouse\Reactions:Reaction');
    }

    protected function getReactedContentRepo()
    {
        return \XF::Repository('ThemeHouse\Reactions:ReactedContent');
    }

    protected function getReactHandlerRepo()
    {
        return \XF::Repository('ThemeHouse\Reactions:ReactHandler');
    }

    /**
     * @param $entity
     * @return \ThemeHouse\Reactions\React\AbstractHandler
     */
    protected function getReactHandlerByEntity(\XF\Mvc\Entity\Entity $entity)
    {
        return $this->getReactHandlerRepo()->getReactHandlerByEntity($entity, false);
    }

    /**
     * @param $contentType
     * @return \ThemeHouse\Reactions\React\AbstractHandler
     */
    protected function getReactHandlerByType($contentType)
    {
        return $this->getReactHandlerRepo()->getReactHandlerByType($contentType, false);
    }
}