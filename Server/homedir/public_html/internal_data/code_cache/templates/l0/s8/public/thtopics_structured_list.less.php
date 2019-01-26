<?php
// FROM HASH: d99b87aeb1bb341a9356fba205e73b31
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '.structItem-topicsForumTitle
{
	float: right;
	max-width: 150px;
	white-space: nowrap;
	overflow: hidden;
	text-overflow: ellipsis;
	color: @xf-textColorMuted;
	font-size: @xf-fontSizeSmaller;
	a {
		color: @xf-textColorMuted;
	}
}

.structItem-topicList {
	margin: 0;
	position: relative;
	line-height: 16px;
	margin: -1px 0 0;
	z-index: 1;

	&-topic {
		margin: 1px 0;
		display: inline-block;
	}
}

.structItem-topicList__spacer {
	display: none;
}

@media (min-width: 1100px) {
	.th_topics_threadListInit .structItem-topicList {
		overflow: visible;
	}

	.structItem-topicList {
		float: right;
		max-width: 150px;
		overflow: hidden;
		margin: 0 0 0 8px;

		&.th_topics__threadWrap--overflowing {
			mask-image: gradient(linear, right top, left top, from(rgba(0,0,0,1)), color-stop(0.75, rgba(0,0,0,1)), to(rgba(0,0,0,0)));
			-webkit-mask-image: -webkit-gradient(linear, right top, left top, from(rgba(0,0,0,1)), color-stop(0.75, rgba(0,0,0,1)), to(rgba(0,0,0,0)));
		}

		&:hover {
			mask-image: none;
			-webkit-mask-image: none;
			& .structItem-topicList__inner {
				max-width: 400px !important;
				padding: 3px;
				margin: -3px;
				border-radius: @xf-borderRadiusLarge;
				background: @xf-contentBg;
				box-shadow: 0 0 0 1px @xf-borderColor;
			}
		}

		.structItem-topicList-topic {
			margin-right: 0;
			margin-left: @xf-paddingSmall;
			display: inline-block;

			&:last-child {
				margin-left: 0;
			}
		}

		&__inner,
		&__spacer {
			display: flex;
			flex-direction: row-reverse;
		}

		&__spacer {
			opacity: 0;
			z-index: -1;
			pointer-events: none;
			display: flex;
		}

		&__inner {
			position: absolute;
			right: 0;
			transition: .2s max-width;
			overflow: hidden;
			&.structItem-topicList__inner--showOverflow {
				overflow: auto;
			}
		}
	}
}';
	return $__finalCompiled;
});