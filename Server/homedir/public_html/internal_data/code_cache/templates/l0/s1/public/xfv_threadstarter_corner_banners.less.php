<?php
// FROM HASH: ea5b5ff5b8663ecb3f7fc12e5db3a91a
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__templater->fn('property', array('xfv_threadstarter_locale', ), false) == 'avatar_banner_tl') {
		$__finalCompiled .= '

.ribbon {
  position: absolute;
  left: -5px; top: -6px;
  z-index: 1;
  overflow: hidden;
  width: 75px;
  height: 75px;
  text-align: right;
}
.ribbon span {
  font-size: ' . $__templater->fn('property', array('xfv_threadstarter_avatar_banner_text_size', ), true) . 'px;
  font-weight: bold;
  ';
		if ($__templater->fn('property', array('xfv_threadstarter_avatar_banner_text_color', ), false)) {
			$__finalCompiled .= '
  color: @xf-xfv_threadstarter_avatar_banner_text_color;
  ';
		} else {
			$__finalCompiled .= '
  color: @xf-linkColor;
  ';
		}
		$__finalCompiled .= '
  text-transform: uppercase;
  text-align: center;
  line-height: 20px;
  transform: rotate(-45deg);
  -webkit-transform: rotate(-45deg);
  width: 96px;
  display: block;
  background: @xf-contentHighlightBg;
  background: @xf-xfv_threadstarter_avatar_banner_color;
  background: linear-gradient(@xf-xfv_threadstarter_avatar_banner_color 0%, @xf-contentHighlightBg  100%);
  box-shadow: 0 6px 10px -5px rgba(0, 0, 0, 0.5);
  position: absolute;
  top: 19px; left: -21px;
}
.ribbon span::before {
  content: "";
  position: absolute; left: 0px; top: 100%;
  z-index: -1;
  border-left: 3px solid rgb(116, 116, 116);
  border-right: 3px solid transparent;
  border-bottom: 3px solid transparent;
  border-top: 3px solid rgb(116, 116, 116);
}
.ribbon span::after {
  content: "";
  position: absolute; right: 0px; top: 100%;
  z-index: -1;
  border-left: 3px solid transparent;
  border-right: 3px solid rgb(116, 116, 116);
  border-bottom: 3px solid transparent;
  border-top: 3px solid rgb(116, 116, 116);
}

@media (max-width: @xf-responsiveMedium)
{

.ribbon {
  position: table;
  left: -0px; top: -0px;
  z-index: 1;
  overflow: hidden;
  width: 48px;
  height: 48px;
  text-align: right;
}
.ribbon span {
  font-size: ' . $__templater->fn('property', array('xfv_threadstarter_avatar_banner_text_size', ), true) . 'px;
  font-weight: bold;
  ';
		if ($__templater->fn('property', array('xfv_threadstarter_avatar_banner_text_color', ), false)) {
			$__finalCompiled .= '
  color: @xf-xfv_threadstarter_avatar_banner_text_color;
  ';
		} else {
			$__finalCompiled .= '
  color: @xf-linkColor;
  ';
		}
		$__finalCompiled .= '
  text-transform: uppercase;
  text-align: center;
  line-height: 20px;
  transform: rotate(-45deg);
  -webkit-transform: rotate(-45deg);
  width: 96px;
  display: block;
  background: @xf-contentHighlightBg;
  background: @xf-xfv_threadstarter_avatar_banner_color;
  background: linear-gradient(@xf-xfv_threadstarter_avatar_banner_color 0%, @xf-contentHighlightBg  100%);
  box-shadow: 0 6px 10px -5px rgba(0, 0, 0, 0.5);
  position: absolute;
  top: 19px; left: -21px;
}
.ribbon span::before {
  content: "";
  position: absolute; left: 0px; top: 100%;
  z-index: -1;
  border-left: 3px solid rgb(116, 116, 116);
  border-right: 3px solid transparent;
  border-bottom: 3px solid transparent;
  border-top: 3px solid rgb(116, 116, 116);
}
.ribbon span::after {
  content: "";
  position: absolute; right: 0px; top: 100%;
  z-index: -1;
  border-left: 3px solid transparent;
  border-right: 3px solid rgb(116, 116, 116);
  border-bottom: 3px solid transparent;
  border-top: 3px solid rgb(116, 116, 116);
}
}

';
	}
	$__finalCompiled .= '

';
	if ($__templater->fn('property', array('xfv_threadstarter_locale', ), false) == 'avatar_banner_tr') {
		$__finalCompiled .= '
.ribbon {
  position: absolute;
  right: -5px; top: -6px;
  z-index: 1;
  overflow: hidden;
  width: 75px; height: 75px;
  text-align: right;
}
.ribbon span {
  font-size: ' . $__templater->fn('property', array('xfv_threadstarter_avatar_banner_text_size', ), true) . 'px;
  font-weight: bold;
  ';
		if ($__templater->fn('property', array('xfv_threadstarter_avatar_banner_text_color', ), false)) {
			$__finalCompiled .= '
  color: @xf-xfv_threadstarter_avatar_banner_text_color;
  ';
		} else {
			$__finalCompiled .= '
  color: @xf-linkColor;
  ';
		}
		$__finalCompiled .= '
  text-transform: uppercase;
  text-align: center;
  line-height: 20px;
  transform: rotate(45deg);
  -webkit-transform: rotate(45deg);
  width: 96px;
  display: block;
  background: @xf-contentHighlightBg;
  background: @xf-xfv_threadstarter_avatar_banner_color;
  background: linear-gradient(@xf-xfv_threadstarter_avatar_banner_color 0%, @xf-contentHighlightBg  100%);
  box-shadow: 0 6px 10px -5px rgba(0, 0, 0, 0.5);
  position: absolute;
  top: 19px; right: -21px;
}
.ribbon span::before {
  content: "";
  position: absolute; left: 0px; top: 100%;
  z-index: -1;
  border-left: 3px solid rgb(116, 116, 116);
  border-right: 3px solid transparent;
  border-bottom: 3px solid transparent;
  border-top: 3px solid rgb(116, 116, 116);
}
.ribbon span::after {
  content: "";
  position: absolute; right: 0px; top: 100%;
  z-index: -1;
  border-left: 3px solid transparent;
  border-right: 3px solid rgb(116, 116, 116);
  border-bottom: 3px solid transparent;
  border-top: 3px solid rgb(116, 116, 116);
}
@media (max-width: @xf-responsiveMedium)
{

.ribbon {
  position: table;
  left: -0px; top: -0px;
  z-index: 1;
  overflow: hidden;
  width: 48px;
  height: 48px;
  text-align: right;
}
.ribbon span {
  font-size: ' . $__templater->fn('property', array('xfv_threadstarter_avatar_banner_text_size', ), true) . 'px;
  font-weight: bold;
  ';
		if ($__templater->fn('property', array('xfv_threadstarter_avatar_banner_text_color', ), false)) {
			$__finalCompiled .= '
  color: @xf-xfv_threadstarter_avatar_banner_text_color;
  ';
		} else {
			$__finalCompiled .= '
  color: @xf-linkColor;
  ';
		}
		$__finalCompiled .= '
  text-transform: uppercase;
  text-align: center;
  line-height: 20px;
  transform: rotate(-45deg);
  -webkit-transform: rotate(-45deg);
  width: 96px;
  display: block;
  background: @xf-contentHighlightBg;
  background: @xf-xfv_threadstarter_avatar_banner_color;
  background: linear-gradient(@xf-xfv_threadstarter_avatar_banner_color 0%, @xf-contentHighlightBg  100%);
  box-shadow: 0 6px 10px -5px rgba(0, 0, 0, 0.5);
  position: absolute;
  top: 19px; left: -21px;
}
.ribbon span::before {
  content: "";
  position: absolute; left: 0px; top: 100%;
  z-index: -1;
  border-left: 3px solid rgb(116, 116, 116);
  border-right: 3px solid transparent;
  border-bottom: 3px solid transparent;
  border-top: 3px solid rgb(116, 116, 116);
}
.ribbon span::after {
  content: "";
  position: absolute; right: 0px; top: 100%;
  z-index: -1;
  border-left: 3px solid transparent;
  border-right: 3px solid rgb(116, 116, 116);
  border-bottom: 3px solid transparent;
  border-top: 3px solid rgb(116, 116, 116);
}
}
';
	}
	return $__finalCompiled;
});