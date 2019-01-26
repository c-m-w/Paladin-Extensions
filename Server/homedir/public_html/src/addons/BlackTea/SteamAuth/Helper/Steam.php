<?php

namespace BlackTea\SteamAuth\Helper;

class Steam
{

    const API_USER = 'https://api.steampowered.com/ISteamUser';
    const API_PLAYER = 'https://api.steampowered.com/IPlayerService';

    /**
     * @var string
     */
    protected $_apiKey;

    /**
     * @var string|null
     */
    protected $_domain;

    /**
     * @var resource
     */
    protected $_curl;

    /**
     * Steam constructor.
     * @param string $apiKey
     * @param null|string $domain
     */
    public function __construct($apiKey, $domain = null)
    {
        $this->_apiKey = $apiKey;
        $this->_domain = $domain;
        $this->_curl = curl_init();

        curl_setopt_array($this->_curl, array(
            CURLOPT_RETURNTRANSFER => true,
            CURLOPT_SSL_VERIFYPEER => false,
            CURLOPT_TIMEOUT => 10,
            CURLOPT_CONNECTTIMEOUT => 10
        ));
    }

    /**
     * Steam destructor.
     */
    public function __destruct()
    {
        curl_close($this->_curl);
    }

    /**
     * @param string $url
     * @param array $params
     * @return string|false
     */
    protected function _request($url, $params = array())
    {
        $fullUrl = $url . '?' . http_build_query($params);
        curl_setopt($this->_curl, CURLOPT_URL, $fullUrl);
        $response = curl_exec($this->_curl);

        if ($response === false) {
            throw new \Exception(curl_error($this->_curl), curl_errno($this->_curl));
        }

        if (isset($params['format']) && $params['format'] == 'json') {
            return json_decode($response, true);
        }

        return $response;
    }

    /**
     * Get Player Summaries
     * @param array $steamIds
     * @return array
     * @throws \Exception
     * @link https://developer.valvesoftware.com/wiki/Steam_Web_API#GetPlayerSummaries_.28v0002.29
     */
    public function getPlayerSummaries($steamIds = array())
    {
        if (count($steamIds) > 100) {
            // TODO ensure $steamIds is <= 100
        }

        $url = self::API_USER . '/GetPlayerSummaries/v0002/';

        $params = array(
            'key' => $this->_apiKey,
            'steamids' => implode(',', $steamIds),
            'format' => 'json'
        );

        $response = $this->_request($url, $params);

        if (!$response || empty($response['response'])) {
            throw new \Exception('Unable to fetch player summaries');
        }

        $players = $response['response']['players'];

        $personaStates = array(
            '0' => \XF::phrase('blacktea_steamauth_visibility_offline'),
            '1' => \XF::phrase('blacktea_steamauth_visibility_online'),
            '2' => \XF::phrase('blacktea_steamauth_visibility_busy'),
            '3' => \XF::phrase('blacktea_steamauth_visibility_away'),
            '4' => \XF::phrase('blacktea_steamauth_visibility_snooze'),
            '5' => \XF::phrase('blacktea_steamauth_visibility_trade'),
            '6' => \XF::phrase('blacktea_steamauth_visibility_play'),
            '7' => \XF::phrase('blacktea_steamauth_visibility_ingame')
        );

        foreach ($players as &$player) {
            if (isset($player['gameid'])) {
                $player['personastate'] = '7';
            }

            $player['personaname'] = htmlspecialchars($player['personaname']);
            $player['personavisibility'] = (string)$personaStates[$player['personastate']];
        }

        return $players;
    }

    public function getOwnedGames($steamId, $includeAppInfo = false, $includeFreeGames = true)
    {
        $url = self::API_PLAYER . '/GetOwnedGames/v0001/';

        $params = array(
            'key' => $this->_apiKey,
            'steamid' => $steamId,
            'include_appinfo' => $includeAppInfo,
            'include_played_free_games' => $includeFreeGames,
            'format' => 'json'
        );

        $response = $this->_request($url, $params);

        if (!$response || !isset($response['response'])) {
            throw new \Exception('Unable to fetch owned games');
        }

        if (empty($response['response'])) {
            return array();
        }

        return $response['response']['games'];
    }

}