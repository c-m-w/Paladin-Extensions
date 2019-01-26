<?php
// FROM HASH: 2286d9993b207cdf437923c7fb383811
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '.itemList-itemTypeIcon
{
	&.itemList-itemTypeIcon--image
	{
		&::after
		{
			.m-faContent(@fa-var-image);
			' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'media',
	), $__vars) . '
		}

		display: none;
	}

	&.itemList-itemTypeIcon--embed
	{
		&::after
		{
			.m-faContent(@fa-var-youtube-play);
			' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'youtube',
	), $__vars) . '
		}
	}

	&.itemList-itemTypeIcon--video
	{
		&::after
		{
			.m-faContent(@fa-var-video-camera);
			' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'video',
	), $__vars) . '
		}
	}

	&.itemList-itemTypeIcon--audio
	{
		&::after
		{
			.m-faContent(@fa-var-music);
			' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'music',
	), $__vars) . '
		}
	}

	&.itemList-itemTypeIcon--embed
	{
		&--applemusic
		{
			&::after { .m-faContent(@fa-var-apple); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'apple',
	), $__vars) . '}
		}

		&--facebook
		{
			&::after { .m-faContent(@fa-var-facebook-official); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'facebook',
	), $__vars) . '}
		}

		&--flickr
		{
			&::after { .m-faContent(@fa-var-flickr); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'video',
	), $__vars) . '}
		}

		&--instagram
		{
			&::after { .m-faContent(@fa-var-instagram); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'instagram',
	), $__vars) . '}
		}

		&--pinterest
		{
			&::after { .m-faContent(@fa-var-pinterest-square); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'pinterest',
	), $__vars) . '}
		}

		&--reddit
		{
			&::after { .m-faContent(@fa-var-reddit-alien); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'reddit',
	), $__vars) . '}
		}

		&--soundcloud
		{
			&::after { .m-faContent(@fa-var-soundcloud); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'soundcloud',
	), $__vars) . '}
		}

		&--spotify
		{
			&::after { .m-faContent(@fa-var-spotify); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'spotify',
	), $__vars) . '}
		}

		&--tumblr
		{
			&::after { .m-faContent(@fa-var-tumblr-square); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'tumblr',
	), $__vars) . '}
		}

		&--twitch
		{
			&::after { .m-faContent(@fa-var-twitch); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'twitch',
	), $__vars) . '}
		}

		&--twitter
		{
			&::after { .m-faContent(@fa-var-twitter); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'twitter',
	), $__vars) . '}
		}

		&--vimeo
		{
			&::after { .m-faContent(@fa-var-vimeo); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'vimeo',
	), $__vars) . '}
		}

		&--youtube
		{
			&::after { .m-faContent(@fa-var-youtube); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'youtube',
	), $__vars) . '}
		}
	}
}

' . $__templater->includeTemplate('xfmg_item_list.less', $__vars);
	return $__finalCompiled;
});