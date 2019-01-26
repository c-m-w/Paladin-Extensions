<?php

namespace ThemeHouse\Reactions\XF\Entity;

class AddOn extends XFCP_AddOn
{
    protected function _postSave()
    {
        parent::_postSave();

        if ($this->isInsert()) {
            \XF::runOnce('addAddOnColumns', function() {
                /** @var \ThemeHouse\Reactions\Repository\Setup $repo */
                $repo = $this->repository('ThemeHouse\Reactions:Setup');
                $repo->setupColumnsForAddOn($this->addon_id);
            });
        }
    }
}