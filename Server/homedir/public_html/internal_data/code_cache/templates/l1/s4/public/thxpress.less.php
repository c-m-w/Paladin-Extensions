<?php
// FROM HASH: 6bc85a52cd67f01d4ab290f1412bede9
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= $__templater->includeTemplate('thxpress_article.less', $__vars) . '
' . $__templater->includeTemplate('thxpress_sidebar.less', $__vars) . '
';
	if ($__templater->fn('property', array('xpress_featuredArticleStyle', ), false) == 'grid') {
		$__finalCompiled .= '
' . $__templater->includeTemplate('thxpress_featuredGrid.less', $__vars) . '
';
	}
	$__finalCompiled .= '

html[class] {
	margin-top: 0 !important;
	#wpadminbar {position: static; z-index: 101;}
}

@overlayColor: mix(#000, @xf-paletteAccent1, 80%);

article > .entry-header {display: none;}

.has-post-thumbnail.xpress_article--featured {

	.block-row {
		background-color: fade(mix(#000, @xf-paletteAccent1, 80%), 60%);
		background: linear-gradient(to bottom, rgba(0, 0, 0, 0.1) 0%, rgba(0, 0, 0, 0.2) 50%, rgba(0, 0, 0, 0.7));
		background: linear-gradient(to bottom, fade(@overlayColor, 10%) 0%, fade(@overlayColor, 20%) 30%, fade(@overlayColor, 70%));
		padding-top: 70px;
		color: rgba(255,255,255,.8);
	}

	.block-body {
		background-size: cover;
		background-position: center;
	}

	.entry-summary, .entry-meta {
		color: rgba(255,255,255,.7);
		a {
			color: inherit; 

			&:hover {color: #fff; }
		}
	}

	.entry-title {
		color: #fff;
	}
}

.xpress_featuredArticles .owl-carousel .xpress_article--featured .block-row {
	min-height: 300px;
}

@supports (display: grid) {
	.xpress_articleList__featured .xpress_article--featured {margin: 0;}
}

.xpress_featuredArticles {

	.block-row {
		display: flex;
		flex-direction: column;
		justify-content: flex-end;
	}
}

';
	if ($__templater->fn('property', array('xpress_articleListLayout', ), false) == 'list') {
		$__finalCompiled .= '

.xpress_articleList {
	article.block {
		.media__object {
			flex-shrink: 0;
		}

		@media (min-width: @xf-xpress_vwColumnBreakpoint) {
			.xpress_articleImage--full {display: none;}
			.xpress_articleImage--thumbnail {display: block;}
			.media--left {margin-right: @xf-paddingLarge; margin-bottom: 0;}
		}
	}
}

';
	} else if ($__templater->fn('property', array('xpress_articleListLayout', ), false) == 'grid') {
		$__finalCompiled .= '

.xpress_articleList {
	columns: 3 300px;
	column-gap: 10px;
	column-fill: auto;
	-moz-column-fill: balance;
	margin: -3px;

	article.block {
		margin-bottom: 10px;
		break-inside: avoid;
		padding: 3px;
	}
}
@supports (-ms-ime-align:auto) {
	.xpress_articleList {
		article.block {
			display: inline-block;
			width: 100%;
		}
	}
}
@media all and (-ms-high-contrast: none), (-ms-high-contrast: active) {
	.xpress_articleList {
		article.block {
			display: inline-block;
			width: 100%;
		}
	}
}
';
	}
	$__finalCompiled .= '

.category-tag {
	display: inline-block;
	max-width: 100%;
	padding: 0 6px 1px;
	margin: 0 0 2px;
	border-radius: @xf-borderRadiusMedium;
	font-size: @xf-fontSizeSmaller;
	.xf-chip();
	&:not(:last-child) {margin-right: 5px;}
}

.tags-links {
	display: flex;
	margin: -3px;
	align-items: center;

	> span {margin-right: 3px;}

	.entry-tags {margin: 3px;}

	.category-tag {margin-bottom: 0;}
}

.xpress_updateLink {
	max-width: 700px;
	margin: 0 auto;
	margin-bottom: @xf-elementSpacer;
}

article.block {
	.media__container {
		display: flex;
		flex-wrap: wrap;

		@media (max-width: @xf-responsiveMedium) {
			flex-direction: column;
		}
	}
	
	iframe {max-width: 100%;}

	.media__body {
		@media (min-width: @xf-responsiveMedium) {
			flex-basis: 300px;
		}
		min-width: 0;
		flex-grow: 1;

		pre {
			word-wrap: break-word;
			white-space: pre-wrap;
		}

	}

	.xpress_articleImage--thumbnail {
		display: none;
	}

	.xpress_articleImage--full {
		overflow: hidden;
		font-size: 0;

		img {
			transition: ease-in .3s transform;
			backface-visibility: hidden;
			&:hover {transform: scale(1.1);}
		}
	}

	.media--left {
		margin-right: 0;
		margin-bottom: @xf-paddingLarge;
	}

	&:not(.has-post-thumbnail) .media--left {margin: 0;}

	.entry-header {margin-bottom: @xf-paddingMedium;}

	.entry-title {
		.xf-thxpress_postExcerptTitle();

		a:not(:hover) {color: inherit;}
	}

	.entry-meta {
		font-size: @xf-fontSizeSmaller;
		color: @xf-textColorMuted;

		.article__author {text-decoration: underline;}

		a {
			color: inherit;
			&:hover {text-decoration: underline;}
		}

		.entry-date {padding-left: 3px;}

		.edit-link {padding-left: 3px;}
	}

	.link-more .screen-reader-text {display: none;}
}

.article-full .entry-footer {
	display: flex;
	align-items: center;
	padding-top: @xf-paddingLarge;
	padding-bottom: @xf-paddingLarge;

	.edit-link {margin-left: auto;}
}

/* styling for article single */

article.article-full {

	.posted-on .screen-reader-text {display: none;}

	.posted-on a + a {}

	.byline {display: none;}

	.entry-header {
		position: relative;
		display: flex;
		align-items: center;
		overflow: hidden;
		justify-content: center;
		background-size: cover;
		background-position: center;
		text-align: center;
		font-size: 14px;

		.entry-meta__author a:last-child {text-decoration: underline;}

		&:before {
			position: absolute;
			top: 0;
			left: 0;
			right: 0;
			bottom: 0;
			background: rgba(0,0,0,.35);
			transition: ease-in .2s background;
		}

		.xpress_entry-header__content {
			position: relative;
			max-width: 800px;
			width: 100%;
			padding: 40px @xf-elementSpacer;
			flex-grow: 1;
			transition: ease-in .2s text-shadow;

		}

		.entry-meta {
			transition: ease-in .2s color;
			margin-top: 10px;
			display: inline-flex;
			align-items: center;
			flex-direction: column;
		}

		.page-title {
			font-size: 28px;
			font-weight: 400;
			margin: 10px 0 0;

			@media (min-width: @xf-responsiveWide) {
				line-height: 1.3;
				font-size: 40px;
			}
		}

		.entry-meta__author {
			display: flex;
			flex-direction: column;

			span.avatar {
				margin-bottom: 10px;
				display: inline-block;
			}
		}

		.entry-meta__postDate {margin-left: 4px;}

		@media (max-width: @xf-responsiveMedium) {
			.entry-meta__author {
				flex-direction: column;
				span.avatar {margin-right: 0; margin-bottom: 5px;}
			}
			.entry-meta__postDate {margin-left: 0; margin-top: 5px;}
		}
	}

	&.has-post-thumbnail {
		.entry-header {
			margin-bottom: 40px;
			padding-top: 100px;

			&:before {content: \'\';}

			.xpress_entry-header__content {color: #fff;}

			.category-tag {
				color: #fff;
				background: none;
				border: none;
				transition: ease-in .2s all;
			}

			.entry-meta {
				color: #fff;
				margin-top: 100px;
				color: rgba(255,255,255,.7);
				display: flex;

				.edit-link {display: block;}

				.entry-meta__author {color: #fff;}

				a {
					color: inherit;
					&:hover {color: #fff;}
				}
			}
		}
	}

	.entry-content {
		font-size: 16px;
		line-height: 2;
		max-width: 700px;
		margin: 0 auto;

		p:not(:last-child) {margin: 0 0 1.5em;}

		';
	if ($__templater->fn('property', array('xpress_dropcap', ), false)) {
		$__finalCompiled .= '
		> p:first-of-type {
			min-height: 100px;
		}

		> p:first-child, > .bbWrapper {
			&:after {
				content: "";
				clear: both;
				display: table;
			}

			&:first-letter {
				font-size: 100px;
				color: @xf-paletteAccent3;
				line-height: 1;
				display: inline-block;
				float: left;
				padding-right: 10px;
				padding-bottom: 10px;
			}
		}
		';
	}
	$__finalCompiled .= '
	}
}

/* category toggle component */

.xpress_categoryToggle {
	display: flex;
	justify-content: center;

	.category-tag {
		padding: 5px 10px;
		border-radius: 20px;

		&:not(:last-child) {margin-right: 10px;}

		.category__count {display: none;}
	}

	.category-tag.current-cat {
		background-color: @xf-paletteAccent3;
		color: #fff;
		border: none;
	}
}

// default WP comment form

.comment-form-comment {
	textarea {
		.xf-input();
		width: 100%;
	}

	label {display: none;}
}

.form-submit .submit {
	.m-buttonBase();
	.xf-buttonDefault();
	.m-buttonBlockColorVariationSimple(xf-default(@xf-buttonDefault--background-color, transparent));
	.xf-buttonPrimary();
	.m-buttonBlockColorVariationSimple(xf-default(@xf-buttonPrimary--background-color, transparent));
}

.logged-in-as {display: none;}

.comment-reply-title {display: none;}

.screen-reader-text {display: none;}

.comment-list .children {
	padding: 0;
	margin-top: @xf-blockPaddingV;
	margin-bottom: 0;
}

@media (min-width: @xf-responsiveWide) {
	.comment-list .children {
		margin-left: 20px;
	}
}

.message + .children,
.children + .message {margin-top: @xf-blockPaddingV;}


/* Comment Editor */
.message--quickReply {
	.comment-reply-title {
		margin: 0;
	}
	.form-submit {
		text-align: right;
		margin-bottom: 0;
	}
}

.fr-element {min-height: 100px !important;}

// 404 page

.search-form {
	display: flex;

	.button {margin-left: 10px;}
}

.error-404 {
	max-width: 600px;
	margin: 50px auto 0;
	text-align: center;

	.page-title {
		font-size: 60px;
		margin: 0;
	}

	input[type="search"] {
		font-size: 16px;
		height: 38px;
	}
}

// forms

input {
	&[type="search"], &[type="text"], &[type="email"], &[type="url"] {
		.xf-input();
	}
}

.comment-form-cookies-consent {
	display: flex;
	align-items: center;
}

.post-navigation {
	margin-top: @xf-elementSpacer;
	.nav-title-icon-wrapper {display: none;}
	.nav-subtitle {display: none;}
	.nav-links {
		display: flex;
		justify-content: space-between;

		> * {flex-grow: 1; flex-basis: 50%;}
	}

	a:hover {text-decoration: none;}

	.nav-previous a:before {
		.m-faBase();
		.m-faContent(@fa-var-arrow-left);
		padding-right: .5em;
		font-size: 18px;
	}

	.nav-previous {padding-right: 5px;}

	.nav-next {
		padding-left: 5px;
		text-align: right;
		justify-content: flex-end;
		a {justify-content: flex-end;}
	}

	.nav-previous,
	.nav-next {
		display: flex;
		color: @xf-linkColor;
		&:hover {color: @xf-linkHoverColor;}
	}

	.nav-next a:after {
		.m-faBase();
		.m-faContent(@fa-var-arrow-right);
		padding-left: .5em;
		font-size: 18px;
	}
}

.p-body-header .thxpress_authorBlock {
	.xf-xpress_authorBlock();
	.p-description  .listInline {
		margin: 0;
		margin-top: 5px;
	}
}

.article-full .thxpress_authorBlock {
	padding-top: @xf-paddingMedium;
	border-top: 2px solid @xf-borderColor;

	.contentRow-figure > .avatar {
		margin-right: 16px;
	}

	.contentRow-main {
		padding-left: 0;
	}

	.p-title {
		font-size: @xf-fontSizeLarger;

		a {color: @xf-textColor;}
	}

	.p-description {
		font-size: @xf-fontSizeSmall;
		color: @xf-textColorMuted;

		.listInline {
			margin: 0;
			margin-top: 5px;
		}
	}
}

/** -- condense message for blog view **/
/* -- moved to UI.X --
.message:not(.message--forceColumns)
{
.message-inner
{
display: block;
}

.message-cell
{
display: block;
.m-clearFix();

&.message-cell--user
{
width: auto;
border-right: none;
border-bottom: @xf-messageUserBlock--border-width solid @xf-messageUserBlock--border-color;
}

&.message-cell--main
{
// padding-left: @xf-messagePadding;
}
}
}

.thThreads__message-userExtras {display: none;}
.thThreads__userExtra--toggle {display: none;}

.message--simple:not(.message--forceColumns),
.message--quickReply:not(.message--forceColumns)
{
.message-cell.message-cell--user
{
display: none;
}
}

.message:not(.message--forceColumns)
{
.message-userArrow
{
top: auto;
right: auto;
bottom: -1px;
left: ((@avatar-s) / 2);

border: none;
.m-triangleUp(xf-default(@xf-messageUserBlock--border-color, transparent), @xf-messagePadding);

&:after
{
top: auto;
right: auto;
left: -(@xf-messagePadding - 1px);
bottom: -@xf-messagePadding;

border: none;
.m-triangleUp(@xf-contentBg, @xf-messagePadding - 1px);
}
}

&.is-mod-selected
{
.message-userArrow:after
{
border-color: transparent;
border-bottom-color: @xf-inlineModHighlightColor;
}
}

.message-user
{
display: flex;

.has-no-flexbox &
{
display: table;
width: 100%;
}
}

.message-avatar
{
margin-bottom: 0;

.has-no-flexbox &
{
display: table-cell;
width: 1%;
}

.avatar
{
.m-avatarSize(@avatar-s);
}
}

.message-userDetails
{
flex: 1;
min-width: 0;
padding-left: @xf-messagePadding;

.has-no-flexbox &
{
display: table-cell;
}
}

.message-name
{
text-align: left;
}

.message-userTitle,
.message-userBanner.userBanner
{
display: inline-block;
text-align: left;
margin: 0;
}

.message-userExtras
{
display: none;
}

.message--deleted
{
.message-userDetails
{
display: block;
}
}
}

*/

/** -- end condense message for blog view **/

#wp-admin-bar-my-account #wp-admin-bar-user-info .avatar {
	.m-avatarSize(64px) !important;
	line-height: .5;
	display: inline-flex;
	align-items: center;
	justify-content: center;
	flex-shrink: 0;

	span {
		font-size: inherit;
		line-height: inherit;
	}
}

#wp-admin-bar-my-account.menupop.with-avatar .ab-item {
	display: inline-flex;
	align-items: center;

	.avatar {
		.m-avatarSize(@avatar-xxs) !important;
		margin-left: 6px;
		display: inline-flex;
		align-items: center;
		justify-content: center;
		flex-shrink: 0;
	}
}

.lg-outer, .lg-backdrop {z-index: 99999;}

.formSubmitRow .formSubmitRow-controls + p {
	display: none;
}';
	return $__finalCompiled;
});