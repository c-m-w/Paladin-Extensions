<?php

/*************************************************************************
 * Warning Logs - XenConcept (c) 2017
 * All Rights Reserved.
 **************************************************************************
 * This file is subject to the terms and conditions defined in the Licence
 * Agreement available at Try it like it buy it :)
 *************************************************************************/

namespace XenConcept\WarningLogs\XF\Repository;

class Warning extends XFCP_Warning
{

    public function clearWarningLog()
    {
        $this->db()->emptyTable('xf_warning');
    }

}