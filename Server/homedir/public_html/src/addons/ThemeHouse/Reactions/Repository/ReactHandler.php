<?php

namespace ThemeHouse\Reactions\Repository;

use ThemeHouse\Reactions\React\AbstractHandler;
use XF\Mvc\Entity\Entity;
use XF\Mvc\Entity\Repository;

class ReactHandler extends Repository
{
    protected $reactHandlers = null;

    /**
     * @return \ThemeHouse\Reactions\React\AbstractHandler[]
     * @throws \Exception
     */
    public function getReactHandlers()
    {
        if ($this->reactHandlers === null) {
            $handlers = [];

            foreach (\XF::app()->getContentTypeField('react_handler_class') AS $contentType => $handlerClass) {
                if (class_exists($handlerClass)) {
                    $eclass = \XF::extendClass($handlerClass);
                    $handlers[$contentType] = [
                        'oclass' => $handlerClass,
                        'eclass' => $eclass,
                        'object' => new $eclass($contentType)
                    ];
                }
            }

            $this->reactHandlers = $handlers;
        }

        return $this->reactHandlers;
    }

    /**
     * @param array $options
     * @return array
     * @throws \Exception
     */
    public function getReactHandlersList(array $options = [])
    {
        $handlers = $this->getReactHandlers();

        $list = [];
        foreach ($handlers as $contentType => $handler) {
            if (in_array('excludeGlobalDisabled', $options) && !$handler['object']->getGlobalStatus()) {
                continue;
            }

            if (in_array('excludeAddOnDisabled', $options) && !$handler['object']->getAddOnStatus()) {
                continue;
            }

            $list[$contentType] = $handler['object']->getTitle();
        }

        return $list;
    }

    /**
     * @param Entity $entity
     * @param bool $throw
     * @return null
     * @throws \Exception
     */
    public function getReactHandlerByEntity(Entity $entity, $throw = false)
    {
        $reactHandler = $this->getReactHandlerByType($entity->getEntityContentType(), $throw);
        if (!$reactHandler) {
            if ($throw) {
                throw new \InvalidArgumentException("No react handler for '{$entity->getEntityContentType()}'");
            }

            return null;
        }

        $reactHandler->setContent($entity);

        return $reactHandler;
    }

    /**
     * @param $type
     * @param bool $throw
     * @return AbstractHandler
     * @throws \Exception
     */
    public function getReactHandlerByType($type, $throw = false)
    {
//        if (is_array($this->reactHandlers) && isset($this->reactHandlers[$type])) {
//            $handlerClass = $this->reactHandlers[$type]['oclass'];
//        } else {
//            $handlerClass = \XF::app()->getContentTypeFieldValue($type, 'react_handler_class');
//        }

        $handlers = $this->getReactHandlers();

        if(empty($handlers[$type]['oclass'])) {
            return null;
        }

        $handlerClass = $handlers[$type]['oclass'];

        if (!$handlerClass) {
            if ($throw) {
                throw new \InvalidArgumentException("No react handler for '$type'");
            }

            return null;
        }

        if (!class_exists($handlerClass)) {
            if ($throw) {
                throw new \InvalidArgumentException("React handler for '$type' does not exist: $handlerClass");
            }

            return null;
        }

        $handlerClass = \XF::extendClass($handlerClass);
        return new $handlerClass($type);

//        if (!isset($this->reactHandlers[$type])) {
//            $eclass = \XF::extendClass($handlerClass);
//            $this->reactHandlers[$type] = [
//                'oclass' => $handlerClass,
//                'eclass' => $eclass,
//                'object' => new $eclass($type)
//            ];
//        }
//
//        return $this->reactHandlers[$type]['object'];
    }
}