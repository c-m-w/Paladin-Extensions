<?php

/*************************************************************************
 * Maintenance Page - XenConcept (c) 2017
 * All Rights Reserved.
 **************************************************************************
 * This file is subject to the terms and conditions defined in the Licence
 * Agreement available at Try it like it buy it :)
 *************************************************************************/

namespace XenConcept\MaintenancePage\Pub\Controller;

use XF\Pub\Controller\AbstractController;

class Maintenance extends AbstractController
{

    public function actionIndex()
    {

        $view = $this->view('XenConcept\MaintenancePage:Maintenance\View', 'xc_maintenance_page_view');
        $view->setPageParam('template', 'xc_maintenance_page_container');

        return $view;
    }

}