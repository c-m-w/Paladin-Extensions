<?php

namespace Siropu\Shoutbox;

trait Shoutbox
{
     public function getShoutboxParams(array $extra = [])
     {
          $collapsed = \XF::app()->request()->getCookie('siropuShoutboxCollapsed');
          $reverse   = $this->getReverseState();
          $lastId    = 0;

          if ($collapsed)
          {
               $shouts = [];
          }
          else
          {
               $shouts = $this->getShoutRepo()
                    ->findShouts()
                    ->fetch();

               if ($shouts->count())
               {
                    if ($reverse)
                    {
                         $shouts = $shouts->reverse();
                         $lastId = $shouts->last()->shout_id;
                    }
                    else
                    {
                         $lastId = $shouts->first()->shout_id;
                    }
               }
          }

          return [
               'shouts'    => $shouts,
               'lastId'    => $lastId,
               'sound'     => \XF::app()->request()->getCookie('siropuShoutboxNoSound') ? 0 : \XF::options()->siropuShoutboxSound,
               'collapsed' => $collapsed,
               'reverse'   => $reverse
          ] + $extra;
     }
     public function getReverseState()
     {
          return (bool) (\XF::app()->request()->getCookie('siropuShoutboxReverse', \XF::options()->siropuShoutboxReverse));
     }
     public function getShoutRepo()
     {
          return \XF::app()->repository('Siropu\Shoutbox:Shout');
     }
}
