<?php
// FROM HASH: a05fa5c4eeef4f5fe8b38c05c6ffe358
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= 'dd pre {
	overflow: auto;
	padding: 4px 15px;
	background: #eee;
	margin-right: 40px;
}

#examples > div {
	display: none;
	pointer-events: none;
}

#examples::before {
    font-family: FontAwesome;
    content: "\\f030";
    background: rgba(221, 221, 221, .8);
    color: white;
    padding: 1em;
    z-index: 100;
    position: relative;
    border-top-left-radius: 5px;
    border-bottom-right-radius: 5px;
    top: 2px;
}

#examples {
    border: 1px solid #ddd;
    border-radius: 5px;
    padding: 10px 0;
}

#examples strong {
	border: 2px solid red;
	border-radius: 5px;
	padding: 0 5px;
	margin: 2px -7px;
}

#examples > div.active {
	display: block;
}

#example-gfonts {
	padding: 20px;
	padding-top: 0;
	font-family: \'Roboto\'
}

#example-gfonts .code-block {
	background: rgba(0,0,0,0.08);
	font-family: \'Roboto Mono\';
	font-size: 12px;
	line-height: 18px;
	margin-top: 16px;
	padding: 11px 16px;
	word-break: break-all;
}

#example-gfonts .link-bar {
	margin-top: 16px;
}

#example-gfonts .link-bar-link {
	display: -webkit-inline-box;
	display: -webkit-inline-flex;
	display: -ms-inline-flexbox;
	display: inline-flex;
	-webkit-align-items: center;
	align-items: center;
	padding-right: 16px;
	margin-right: 4px;
	color: #ff5252;
	fill: #ff5252;
	font-weight: 500;
	text-decoration: none;
	cursor: pointer;
}

#example-gfonts .link-bar-link.link-is-inactive {
	opacity: .7;
}

#example-gfonts .collection-drawer-help-text {
	color: rgba(0,0,0,0.87);
	font-weight: 400;
	line-height: 20px;
	margin: 0;
	padding: 0;
	border: 0;
	font: inherit;
	vertical-align: baseline;
}

#example-gfonts .collection-drawer-title {
	margin: 0;
	padding: 0;
	border: 0;
	font: inherit;
	vertical-align: baseline;
	color: rgba(0,0,0,0.87);
	font-size: 14px;
	font-weight: 500;
	margin-bottom: 9px;
}
#example-webtype,
#example-typekit {
	padding: 20px;
	padding-top: 0;
}

#example-typekit .neue-family-font-details__pre {
	background-color: #fbfaf8;
	border: 1px solid #ccc;
	border-radius: 3px;
	font-size: 12px;
	line-height: 2;
	margin-top: 20px;
	max-height: 150px;
	overflow-x: auto;
	-ms-overflow-style: none;
	padding: 8px 12px;
}

#example-typekit .neue-tabs {
	border-bottom: 1px solid #ccc;
	padding: 0;
	margin: 0;
}

#example-typekit .neue-tabs .neue-tabs__tab {
	display: inline-block;
	color: #07b57a;
	cursor: pointer;
	font-size: 16px;
	font-weight: 700;
	letter-spacing: .1em;
	padding: 0 0 20px;
	position: relative;
	text-transform: uppercase;
	-webkit-transition: color .1s;
	transition: color .1s;
	vertical-align: middle;
	-webkit-font-smoothing: antialiased;
}

#example-typekit .neue-tabs .neue-tabs__tab:not(:last-child) {
	margin-right: 20px;
}

#example-typekit .neue-tabs .neue-tabs__tab--active {
	color: #333;
}

#example-typekit .neue-tabs__tab--active::before {
	border: 7px solid rgba(255,255,255,0);
	border-bottom-color: #b3b3b3;
	border-top-width: 0;
	bottom: 0;
	content: \'\';
	left: 50%;
	margin-left: -7px;
	position: absolute;
}

#example-typekit .neue-tabs__tab--active::after {
	border: 7px solid rgba(255,255,255,0);
	border-top-width: 0;
	border-bottom-color: #fff;
	bottom: -1px;
	content: \'\';
	left: 50%;
	margin-left: -7px;
	position: absolute;
}

#example-typekit p {
	color: #666;
	font-size: 13px;
	margin: 0;
}

#example-typekit .a {
	color: #07b57a;
	-webkit-transition: color .1s, background-color .1s, border-color .1s;
	transition: color .1s, background-color .1s, border-color .1s;
	text-decoration: underline;
	cursor: pointer;
}

#example-typekit a:hover {
	color: #0b714e;
}

#example-webtype .clearafter:after { content:"."; display: block; height:0; clear:both; visibility:hidden; }
#example-webtype .clearafter { display: inline-block; height: 1%; }

#example-webtype .text-area {
	padding: 15px;
    border: #B3B3B3 solid 1px;
    background: #fff;
    width: 487px;
	font: 13.3333px Arial;
	font-family: monospace;
}

#example-fonts {
	font-family: inherit;
    font-weight: 400;
    font-size: 16px;
    line-height: 1.5;
    margin-bottom: 30px;
    text-rendering: optimizeLegibility;
	color: #777;
	margin-top: -20px;
	padding: 0 20px 40px;
}

#example-fonts .link-action {
	background-color: rgba(108, 181, 217, 0.584);
	background-image: -webkit-linear-gradient(top, rgb(238, 239, 235) 0px, rgb(242, 242, 242) 100%);
	background-origin: padding-box;
	border: 1px solid rgb(242, 242, 242);
	border-radius: 2px;
	box-shadow: rgba(0, 0, 0, 0.15) 0px 2px 2px 0.9px;
	box-sizing: border-box;
	color: rgb(0, 0, 0);
	cursor: pointer;
	display: block;
	float: right;
	font-family: "Arial Narrow", Arial, sans-serif;
	font-size: 13px;
	height: 32px;
	margin-top: 10px;
	padding: 8px 8px 5px;
	text-decoration-color: rgb(0, 0, 0);
	text-decoration-line: none;
	text-decoration-style: solid;
	text-size-adjust: 100%;
	text-transform: uppercase;
	transition-delay: 0s;
	transition-duration: 0.3s;
	transition-property: background;
	transition-timing-function: ease-out;
	width: 94px;
	-webkit-font-smoothing: antialiased;
}

#example-fonts .text-area {	
	color: #777;
	border: none;
    -moz-border-radius: 5px;
    -webkit-border-radius: 5px;
    border-radius: 5px;
    border: 2px solid rgba(0,0,0,.2);
    display: inline-block;
    margin-bottom: 0;
	background-color: #DDD;
    cursor: default;
	font: 400 9pt Courier,\'Courier New\',Verdana;
    height: 80px;
    margin: 0;
    padding-left: 0;
    padding-right: 0;
    resize: none;
}';
	return $__finalCompiled;
});