<?php

namespace ThemeHouse\Bookmarks;

use XF\AddOn\AbstractSetup;
use XF\AddOn\StepRunnerInstallTrait;
use XF\AddOn\StepRunnerUninstallTrait;
use XF\AddOn\StepRunnerUpgradeTrait;

class Setup extends AbstractSetup
{
	use StepRunnerInstallTrait;
	use StepRunnerUpgradeTrait;
	use StepRunnerUninstallTrait;

	public function installStep1()
    {
        $schemaManager = $this->schemaManager();

        $schemaManager->createTable('xf_th_bookmark', function(\XF\Db\Schema\Create $table) {
            $table->addColumn('bookmark_id', 'int')->autoIncrement();
            $table->addColumn('note', 'varchar', 250);
            $table->addColumn('sticky', 'bool')->setDefault(0);
            $table->addColumn('public', 'bool')->setDefault(1);
            $table->addColumn('user_id', 'int');
            $table->addColumn('content_id', 'int');
            $table->addColumn('content_type', 'varbinary', 25);
            $table->addColumn('bookmark_date', 'int');
        });
    }

    public function installStep2()
    {
        $this->applyGlobalPermission('th_bookmarks', 'canBookmark', 'forum', 'like');
    }

    public function uninstallStep1()
    {
        $schemaManager = $this->schemaManager();

        $schemaManager->dropTable('xf_th_bookmark');
    }

    protected function activateNewContentTypes(Array $newContentTypes = [])
    {
        $options = \XF::options();

        $newValues = $options->th_enableContentTypes_bookmarks;
        foreach ($newContentTypes as $contentType) {
            if (!in_array($contentType, $options->th_enableContentTypes_bookmarks)) {
                $newValues[] = $contentType;
            }
        }

        \XF::repository('XF:Option')->updateOptions([
            'th_enableContentTypes_bookmarks' => $newValues,
        ]);
    }
}