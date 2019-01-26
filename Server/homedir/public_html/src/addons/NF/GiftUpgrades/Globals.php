<?php

namespace NF\GiftUpgrades;

// This class is used to encapsulate global state between layers without using $GLOBAL[] or
// relying on the consumer being loaded correctly by the dynamic class autoloader
class Globals
{
    public static $isGift = null;
    public static $payUserId = null;
    public static $payUsername = null;

    public static $giftTo = null;
    public static $isAnonymous = null;

    private function __construct()
    {
    }
}