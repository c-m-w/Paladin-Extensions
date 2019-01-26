<?php

namespace ThemeHouse\Bookmarks\Import\Importer;

use XF\Import\Importer\AbstractImporter;

abstract class AbstractBookmarkImporter extends AbstractImporter
{
    public function canRetainIds()
    {
        return false;
    }

    public function getFinalizeJobs(array $stepsRun)
    {
        return [];
    }

    public function resetDataForRetainIds()
    {
        return false;
    }
}