<?php
// FROM HASH: 443ad961f8991b254fda14ab8f1dce51
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '/*!
* froala_editor v2.7.6 (https://www.froala.com/wysiwyg-editor)
* License https://froala.com/wysiwyg-editor/terms/
* Copyright 2014-2018 Froala Labs
*/

.clearfix::after {
	clear: both;
	display: block;
	content: "";
	height: 0
}

.hide-by-clipping {
	position: absolute;
	width: 1px;
	height: 1px;
	padding: 0;
	margin: -1px;
	overflow: hidden;
	clip: rect(0, 0, 0, 0);
	border: 0
}

.fr-modal {
	.fr-modal-wrapper {
		.fr-modal-body {
			.fr-special-characters-modal {
				background: @xf-pageBg;
				text-align: left;
				padding: 20px 20px 10px;

				.fr-special-characters-list {
					margin-bottom: 20px
				}

				.fr-special-characters-title {
					font-weight: 700;
					font-size: 14px;
					padding: 6px 0 4px;
					margin: 0 0 5px;
				}

				.fr-special-character {
					display: inline-block;
					font-size: 16px;
					width: 20px;
					height: 20px;
					padding: 5px;
					line-height: 20px;
					cursor: default;
					font-weight: 400;
					-webkit-box-sizing: content-box;
					-moz-box-sizing: content-box;
					box-sizing: content-box;
					text-align: center;
					border: 1px solid #ccc;
					margin: -1px 0 0 -1px;
				}
			}
		}
	}
}';
	return $__finalCompiled;
});