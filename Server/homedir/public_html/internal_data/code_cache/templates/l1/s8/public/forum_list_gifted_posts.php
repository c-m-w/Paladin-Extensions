<?php
// FROM HASH: fba5b75b3bc9a539d9697bd4e92dde33
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<xen:if is="' . $__templater->escape($__vars['giftedPosts']) . '">
    <style>
        .giftedPostList .snippet {
            font-size: 11px;
            color: {xen:property dimmedTextColor};
        }
        .giftedPostList .postListItem {
            padding-bottom:2px;
        }
        .giftedPostList .postListItem:last-child {
            padding-bottom:0px;
        }
    </style>
    <div class="section giftedPostList">
        <div class="secondaryContent">
            <h3>{xen:phrase nf_recent_gifted_posts}</h3>

            <ul>
                <xen:foreach loop="' . $__templater->escape($__vars['giftedPosts']) . '" value="' . $__templater->escape($__vars['post']) . '">
                    <li id="post-' . $__templater->escape($__vars['post']['post_id']) . '" class="threadListItem postListItem {xen:if $post.isIgnored, \' ignored\'}" data-author="' . $__templater->escape($__vars['post']['username']) . '">
                        <div class="postInfo">

                            <div class="messageContent">
                                <div class="title">
                                    <a href="{xen:link posts, $post}">{xen:helper threadPrefix, $post}' . $__templater->escape($__vars['post']['title']) . '</a>
                                </div>

                                <xen:if is="' . $__templater->escape($__vars['xenOptions']['nf_giftSnippetLength']) . ' > 0">
                                    <div class="snippet muted">
                                        {xen:helper snippet, $post.message, $xenOptions.nf_giftSnippetLength, {xen:array \'stripQuote=1\', \'fromStart=1\'}}
                                    </div>
                                </xen:if>
                            </div>

                            <div class="additionalRow muted">
                                {xen:phrase post_by}: <xen:username user="$post" />,
                                <xen:datetime time="' . $__templater->escape($__vars['post']['post_date']) . '" />
                            </div>

                            <div class="additionalRow muted">
                                <a href="{xen:link forums, $post.forum}" class="forumLink">' . $__templater->escape($__vars['post']['forum']['title']) . '</a>
                            </div>
                        </div>
                    </li>
                </xen:foreach>
            </ul>
        </div>
    </div>
</xen:if>';
	return $__finalCompiled;
});