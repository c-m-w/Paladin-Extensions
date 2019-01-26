<?php

namespace ThemeHouse\Reactions\Repository;

use XF\Db\Schema\Alter;
use XF\Mvc\Entity\Repository;

class Setup extends Repository
{
    public function setupColumnsForAddOn($addOnId)
    {
        $schemaManager = $this->db()->getSchemaManager();

        if ($addOnId === 'XFRM') {
            $schemaManager->alterTable('xf_rm_resource_update', function(Alter $table) {
                $table->addColumn('react_users', 'mediumblob')->nullable();
            });
        }

        if ($addOnId === 'XFMG') {
            $schemaManager->alterTable('xf_mg_media_item', function(Alter $table) {
                $table->addColumn('react_users', 'mediumblob')->nullable();
            });
            $schemaManager->alterTable('xf_mg_comment', function(Alter $table) {
                $table->addColumn('react_users', 'mediumblob')->nullable();
            });

            $schemaManager->alterTable('xf_mg_album', function (Alter $table) {
                $table->addColumn('react_users', 'blob')->nullable();
            });
        }
    }
}