<?php
// FROM HASH: 7db139fdb052c394bfaf26e0bc80ba16
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '/* CSS3 Hover Effects */
.img-box {
	display: block;
	width: 100%;
	height: 100%;
	border-radius: 5px;
	-webkit-transform: scale(1, 1);
	-moz-transform: scale(1, 1);
	-ms-transform: scale(1, 1);
	-o-transform: scale(1, 1);
	transform: scale(1, 1);
	-webkit-transition: all 0.4s ease-in-out;
	-moz-transition: all 0.4s ease-in-out;
	-ms-transition: all 0.4s ease-in-out;
	-o-transition: all 0.4s ease-in-out;
	transition: all 0.4s ease-in-out;
	-webkit-backface-visibility: hidden;
	-moz-backface-visibility: hidden;
	-ms-backface-visibility: hidden;
	-o-backface-visibility: hidden;
	backface-visibility: hidden;
	position: relative;
	img {
		display: block;
    	position: relative;
		border-radius: 5px;
		max-width: 100%;
		max-height: 100%;
		-webkit-transition: all 0.4s ease-in-out;
		-moz-transition: all 0.4s ease-in-out;
		-ms-transition: all 0.4s ease-in-out;
		-o-transition: all 0.4s ease-in-out;
		transition: all 0.4s ease-in-out;
	}
}
.info-box {
	display: block;
	width: 100%;
	height: 100%;
	border-radius: 5px;
	-webkit-transform: scale(1, 1);
	-moz-transform: scale(1, 1);
	-ms-transform: scale(1, 1);
	-o-transform: scale(1, 1);
	transform: scale(1, 1);
	-webkit-transition: all 0.4s ease-in-out;
	-moz-transition: all 0.4s ease-in-out;
	-ms-transition: all 0.4s ease-in-out;
	-o-transition: all 0.4s ease-in-out;
	transition: all 0.4s ease-in-out;
	-webkit-backface-visibility: hidden;
	-moz-backface-visibility: hidden;
	-ms-backface-visibility: hidden;
	-o-backface-visibility: hidden;
	backface-visibility: hidden;
	top: 0;
	left: 0;
	position: absolute;
	text-align: center;
	img {
		display: block;
		position: relative;
		border-radius: 5px;
		max-width: 100%;
		max-height: 100%;
		-webkit-transition: all 0.4s ease-in-out;
		-moz-transition: all 0.4s ease-in-out;
		-ms-transition: all 0.4s ease-in-out;
		-o-transition: all 0.4s ease-in-out;
		transition: all 0.4s ease-in-out;
	}
	.info-content {
		h3 {
			a {
				color: #fff;
			}
		}
		p {
			color: #fff;
		}
		.u-muted {
			color: #fff;
			font-weight: 400;
		}
		display: block;
		position: relative;
		padding: 2%;
		float: left;
		left: 50%;
		top: 50%;
		position: relative;
		-webkit-transform: translateX(-50%) translateY(-50%);
		-moz-transform: translateX(-50%) translateY(-50%);
		-ms-transform: translateX(-50%) translateY(-50%);
		-o-transform: translateX(-50%) translateY(-50%);
		transform: translateX(-50%) translateY(-50%);
	}
}
.info-content {
	.smallest-content {
		a {
			color: #fff;
			padding: 8px;
		}
		.u-muted {
			color: #fff;
		}
		padding-top: 5px;
	}
}
.separator {
	display: block;
	position: relative;
	height: 1px;
	width: 60%;
	margin: 10px auto;
	background: rgba(255, 255, 255, 0.5);
	clear: both;
}
.round-box {
	overflow: hidden;
	-webkit-border-radius: 50%;
	-moz-border-radius: 50%;
	-ms-border-radius: 50%;
	-o-border-radius: 50%;
	border-radius: 50%;
	.img-box {
		overflow: hidden;
		-webkit-border-radius: 50%;
		-moz-border-radius: 50%;
		-ms-border-radius: 50%;
		-o-border-radius: 50%;
		border-radius: 50%;
	}
	.info-box {
		overflow: hidden;
		-webkit-border-radius: 50%;
		-moz-border-radius: 50%;
		-ms-border-radius: 50%;
		-o-border-radius: 50%;
		border-radius: 50%;
	}
	.info-content {
		overflow: hidden;
		-webkit-border-radius: 50%;
		-moz-border-radius: 50%;
		-ms-border-radius: 50%;
		-o-border-radius: 50%;
		border-radius: 50%;
	}
	img {
		overflow: hidden;
		-webkit-border-radius: 50%;
		-moz-border-radius: 50%;
		-ms-border-radius: 50%;
		-o-border-radius: 50%;
		border-radius: 50%;
	}
}
.round-box.bubble-effect {
	overflow: visible;
}
.round-box.flip-effect {
	overflow: visible;
}
.round-box.over-flip-effect {
	overflow: visible;
}
.round-box.flip-back-effect {
	overflow: visible;
}
.round-box.switch-3d-effect {
	overflow: visible;
}
.round-box.flip-forward-effect {
	overflow: visible;
}
.trans-effect {
	display: block;
	overflow: hidden;
	position: relative;
	border-radius: 5px;
	box-shadow: 0 3px 15px -2px rgba(94,94,94,.65);
	-webkit-transform: translate3d(0, 0, 0);
	-moz-transform: translate3d(0, 0, 0);
	-ms-transform: translate3d(0, 0, 0);
	-o-transform: translate3d(0, 0, 0);
	transform: translate3d(0, 0, 0);
	.info-box {
		background: @xf-xrImageHoverEffectColor;
	}
}
.trans-effect.top {
	.img-box {
		-webkit-transform: translate3d(0, 0, 0);
		-moz-transform: translate3d(0, 0, 0);
		-ms-transform: translate3d(0, 0, 0);
		-o-transform: translate3d(0, 0, 0);
		transform: translate3d(0, 0, 0);
	}
	.info-box {
		-webkit-transform: translate3d(0, 100%, 0);
		-moz-transform: translate3d(0, 100%, 0);
		-ms-transform: translate3d(0, 100%, 0);
		-o-transform: translate3d(0, 100%, 0);
		transform: translate3d(0, 100%, 0);
	}
	&:hover {
		.img-box {
			-webkit-transform: translate3d(0, -100%, 0);
			-moz-transform: translate3d(0, -100%, 0);
			-ms-transform: translate3d(0, -100%, 0);
			-o-transform: translate3d(0, -100%, 0);
			transform: translate3d(0, -100%, 0);
		}
		.info-box {
			-webkit-transform: translate3d(0, 0, 0);
			-moz-transform: translate3d(0, 0, 0);
			-ms-transform: translate3d(0, 0, 0);
			-o-transform: translate3d(0, 0, 0);
			transform: translate3d(0, 0, 0);
		}
	}
}
.trans-effect.bottom {
	.img-box {
		-webkit-transform: translate3d(0, 0, 0);
		-moz-transform: translate3d(0, 0, 0);
		-ms-transform: translate3d(0, 0, 0);
		-o-transform: translate3d(0, 0, 0);
		transform: translate3d(0, 0, 0);
	}
	.info-box {
		-webkit-transform: translate3d(0, -100%, 0);
		-moz-transform: translate3d(0, -100%, 0);
		-ms-transform: translate3d(0, -100%, 0);
		-o-transform: translate3d(0, -100%, 0);
		transform: translate3d(0, -100%, 0);
	}
	&:hover {
		.img-box {
			-webkit-transform: translate3d(0, 100%, 0);
			-moz-transform: translate3d(0, 100%, 0);
			-ms-transform: translate3d(0, 100%, 0);
			-o-transform: translate3d(0, 100%, 0);
			transform: translate3d(0, 100%, 0);
		}
		.info-box {
			-webkit-transform: translate3d(0, 0, 0);
			-moz-transform: translate3d(0, 0, 0);
			-ms-transform: translate3d(0, 0, 0);
			-o-transform: translate3d(0, 0, 0);
			transform: translate3d(0, 0, 0);
		}
	}
}
.trans-effect.left {
	.img-box {
		-webkit-transform: translate3d(0, 0, 0);
		-moz-transform: translate3d(0, 0, 0);
		-ms-transform: translate3d(0, 0, 0);
		-o-transform: translate3d(0, 0, 0);
		transform: translate3d(0, 0, 0);
	}
	.info-box {
		-webkit-transform: translate3d(100%, 0, 0);
		-moz-transform: translate3d(100%, 0, 0);
		-ms-transform: translate3d(100%, 0, 0);
		-o-transform: translate3d(100%, 0, 0);
		transform: translate3d(100%, 0, 0);
	}
	&:hover {
		.img-box {
			-webkit-transform: translate3d(-100%, 0, 0);
			-moz-transform: translate3d(-100%, 0, 0);
			-ms-transform: translate3d(-100%, 0, 0);
			-o-transform: translate3d(-100%, 0, 0);
			transform: translate3d(-100%, 0, 0);
		}
		.info-box {
			-webkit-transform: translate3d(0, 0, 0);
			-moz-transform: translate3d(0, 0, 0);
			-ms-transform: translate3d(0, 0, 0);
			-o-transform: translate3d(0, 0, 0);
			transform: translate3d(0, 0, 0);
		}
	}
}
.trans-effect.right {
	.img-box {
		-webkit-transform: translate3d(0, 0, 0);
		-moz-transform: translate3d(0, 0, 0);
		-ms-transform: translate3d(0, 0, 0);
		-o-transform: translate3d(0, 0, 0);
		transform: translate3d(0, 0, 0);
	}
	.info-box {
		-webkit-transform: translate3d(-100%, 0, 0);
		-moz-transform: translate3d(-100%, 0, 0);
		-ms-transform: translate3d(-100%, 0, 0);
		-o-transform: translate3d(-100%, 0, 0);
		transform: translate3d(-100%, 0, 0);
	}
	&:hover {
		.img-box {
			-webkit-transform: translate3d(100%, 0, 0);
			-moz-transform: translate3d(100%, 0, 0);
			-ms-transform: translate3d(100%, 0, 0);
			-o-transform: translate3d(100%, 0, 0);
			transform: translate3d(100%, 0, 0);
		}
		.info-box {
			-webkit-transform: translate3d(0, 0, 0);
			-moz-transform: translate3d(0, 0, 0);
			-ms-transform: translate3d(0, 0, 0);
			-o-transform: translate3d(0, 0, 0);
			transform: translate3d(0, 0, 0);
		}
	}
}
.fade-in-effect {
	display: block;
	overflow: hidden;
	position: relative;
	border-radius: 5px;
	box-shadow: 0 3px 15px -2px rgba(94,94,94,.65);
	-webkit-transform: translate3d(0, 0, 0);
	-moz-transform: translate3d(0, 0, 0);
	-ms-transform: translate3d(0, 0, 0);
	-o-transform: translate3d(0, 0, 0);
	transform: translate3d(0, 0, 0);
	.img-box {
		top: 0;
		right: 0;
		bottom: 0;
		left: 0;
		color: #e6e6e6;
		z-index: 0;
		a {
			color: #fff;
			&:active {
				color: #fff;
				&:hover {
					color: #f2f2f2;
				}
			}
			&:focus {
				color: #fff;
				&:hover {
					color: #f2f2f2;
				}
			}
			&:hover {
				color: #f2f2f2;
			}
		}
	}
	.info-box {
		top: 0;
		right: 0;
		bottom: 0;
		left: 0;
		color: #e6e6e6;
		z-index: 1;
		background-color: rgba(0, 0, 0, 0.5);
		filter: alpha(opacity=0);
		-wekbit-opacity: 0;
		-moz-opacity: 0;
		opacity: 0;
		a {
			color: #fff;
			&:active {
				color: #fff;
				&:hover {
					color: #f2f2f2;
				}
			}
			&:focus {
				color: #fff;
				&:hover {
					color: #f2f2f2;
				}
			}
			&:hover {
				color: #f2f2f2;
			}
		}
	}
	&:hover {
		.info-box {
			filter: alpha(opacity=100);
			-wekbit-opacity: 1;
			-moz-opacity: 1;
			opacity: 1;
		}
	}
}
.over-trans-effect {
	display: block;
	overflow: hidden;
	position: relative;
	border-radius: 5px;
	box-shadow: 0 3px 15px -2px rgba(94,94,94,.65);
	-webkit-transform: translate3d(0, 0, 0);
	-moz-transform: translate3d(0, 0, 0);
	-ms-transform: translate3d(0, 0, 0);
	-o-transform: translate3d(0, 0, 0);
	transform: translate3d(0, 0, 0);
	.img-box {
		color: #e6e6e6;
		a {
			color: #fff;
			&:active {
				color: #fff;
				&:hover {
					color: #f2f2f2;
				}
			}
			&:focus {
				color: #fff;
				&:hover {
					color: #f2f2f2;
				}
			}
			&:hover {
				color: #f2f2f2;
			}
		}
	}
	.info-box {
		color: #e6e6e6;
		opacity: 0.85;
		background: @xf-xrImageHoverEffectColor;
		a {
			color: #fff;
			&:active {
				color: #fff;
				&:hover {
					color: #f2f2f2;
				}
			}
			&:focus {
				color: #fff;
				&:hover {
					color: #f2f2f2;
				}
			}
			&:hover {
				color: #f2f2f2;
			}
		}
	}
}
.over-trans-effect.top {
	.img-box {
		-webkit-transform: translate3d(0, 0, 0);
		-moz-transform: translate3d(0, 0, 0);
		-ms-transform: translate3d(0, 0, 0);
		-o-transform: translate3d(0, 0, 0);
		transform: translate3d(0, 0, 0);
	}
	.info-box {
		-webkit-transform: translate3d(0, -100%, 0);
		-moz-transform: translate3d(0, -100%, 0);
		-ms-transform: translate3d(0, -100%, 0);
		-o-transform: translate3d(0, -100%, 0);
		transform: translate3d(0, -100%, 0);
	}
	&:hover {
		.info-box {
			-webkit-transform: translate3d(0, 0, 0);
			-moz-transform: translate3d(0, 0, 0);
			-ms-transform: translate3d(0, 0, 0);
			-o-transform: translate3d(0, 0, 0);
			transform: translate3d(0, 0, 0);
		}
	}
}
.over-trans-effect.bottom {
	.img-box {
		-webkit-transform: translate3d(0, 0, 0);
		-moz-transform: translate3d(0, 0, 0);
		-ms-transform: translate3d(0, 0, 0);
		-o-transform: translate3d(0, 0, 0);
		transform: translate3d(0, 0, 0);
	}
	.info-box {
		-webkit-transform: translate3d(0, 100%, 0);
		-moz-transform: translate3d(0, 100%, 0);
		-ms-transform: translate3d(0, 100%, 0);
		-o-transform: translate3d(0, 100%, 0);
		transform: translate3d(0, 100%, 0);
	}
	&:hover {
		.info-box {
			-webkit-transform: translate3d(0, 0, 0);
			-moz-transform: translate3d(0, 0, 0);
			-ms-transform: translate3d(0, 0, 0);
			-o-transform: translate3d(0, 0, 0);
			transform: translate3d(0, 0, 0);
		}
	}
}
.over-trans-effect.left {
	.img-box {
		-webkit-transform: translate3d(0, 0, 0);
		-moz-transform: translate3d(0, 0, 0);
		-ms-transform: translate3d(0, 0, 0);
		-o-transform: translate3d(0, 0, 0);
		transform: translate3d(0, 0, 0);
	}
	.info-box {
		-webkit-transform: translate3d(-100%, 0, 0);
		-moz-transform: translate3d(-100%, 0, 0);
		-ms-transform: translate3d(-100%, 0, 0);
		-o-transform: translate3d(-100%, 0, 0);
		transform: translate3d(-100%, 0, 0);
	}
	&:hover {
		.info-box {
			-webkit-transform: translate3d(0, 0, 0);
			-moz-transform: translate3d(0, 0, 0);
			-ms-transform: translate3d(0, 0, 0);
			-o-transform: translate3d(0, 0, 0);
			transform: translate3d(0, 0, 0);
		}
	}
}
.over-trans-effect.right {
	.img-box {
		-webkit-transform: translate3d(0, 0, 0);
		-moz-transform: translate3d(0, 0, 0);
		-ms-transform: translate3d(0, 0, 0);
		-o-transform: translate3d(0, 0, 0);
		transform: translate3d(0, 0, 0);
	}
	.info-box {
		-webkit-transform: translate3d(100%, 0, 0);
		-moz-transform: translate3d(100%, 0, 0);
		-ms-transform: translate3d(100%, 0, 0);
		-o-transform: translate3d(100%, 0, 0);
		transform: translate3d(100%, 0, 0);
	}
	&:hover {
		.info-box {
			-webkit-transform: translate3d(0, 0, 0);
			-moz-transform: translate3d(0, 0, 0);
			-ms-transform: translate3d(0, 0, 0);
			-o-transform: translate3d(0, 0, 0);
			transform: translate3d(0, 0, 0);
		}
	}
}
.zoom-out-effect {
	display: block;
	overflow: hidden;
	position: relative;
	border-radius: 5px;
	box-shadow: 0 3px 15px -2px rgba(94,94,94,.65);
	-webkit-transform: translate3d(0, 0, 0);
	-moz-transform: translate3d(0, 0, 0);
	-ms-transform: translate3d(0, 0, 0);
	-o-transform: translate3d(0, 0, 0);
	transform: translate3d(0, 0, 0);
	.img-box {
		top: 0;
		right: 0;
		bottom: 0;
		left: 0;
		color: #e6e6e6;
		z-index: 0;
		a {
			color: #fff;
			&:active {
				color: #fff;
				&:hover {
					color: #f2f2f2;
				}
			}
			&:focus {
				color: #fff;
				&:hover {
					color: #f2f2f2;
				}
			}
			&:hover {
				color: #f2f2f2;
			}
		}
	}
	.info-box {
		top: 0;
		right: 0;
		bottom: 0;
		left: 0;
		color: #e6e6e6;
		z-index: 1;
		background: @xf-xrImageHoverEffectColor;
		filter: alpha(opacity=0);
		-wekbit-opacity: 0;
		-moz-opacity: 0;
		opacity: 0;
		a {
			color: #fff;
			&:active {
				color: #fff;
				&:hover {
					color: #f2f2f2;
				}
			}
			&:focus {
				color: #fff;
				&:hover {
					color: #f2f2f2;
				}
			}
			&:hover {
				color: #f2f2f2;
			}
		}
	}
	&:hover {
		.info-box {
			filter: alpha(opacity=100);
			-wekbit-opacity: 1;
			-moz-opacity: 1;
			opacity: 0.85;
		}
		.img-box {
			-webkit-transform: translateZ(0) scale(1.15, 1.15);
			-moz-transform: translateZ(0) scale(1.15, 1.15);
			-ms-transform: translateZ(0) scale(1.15, 1.15);
			-o-transform: translateZ(0) scale(1.15, 1.15);
			transform: translateZ(0) scale(1.15, 1.15);
		}
	}
}
.flip-effect {
	display: block;
	position: relative;
	-webkit-perspective: 1000px;
	-moz-perspective: 1000px;
	-ms-perspective: 1000px;
	-o-perspective: 1000px;
	perspective: 1000px;
	-webkit-transform: translate3d(0, 0, 0);
	-moz-transform: translate3d(0, 0, 0);
	-ms-transform: translate3d(0, 0, 0);
	-o-transform: translate3d(0, 0, 0);
	transform: translate3d(0, 0, 0);
	.img-box {
		top: 0;
		right: 0;
		bottom: 0;
		left: 0;
		z-index: 0;
		a {
			color: #fff;
			&:active {
				color: #fff;
				&:hover {
					color: #f2f2f2;
				}
			}
			&:focus {
				color: #fff;
				&:hover {
					color: #f2f2f2;
				}
			}
			&:hover {
				color: #f2f2f2;
			}
		}
	}
	.info-box {
		top: 0;
		right: 0;
		bottom: 0;
		left: 0;
		a {
			color: #fff;
			&:active {
				color: #fff;
				&:hover {
					color: #f2f2f2;
				}
			}
			&:focus {
				color: #fff;
				&:hover {
					color: #f2f2f2;
				}
			}
			&:hover {
				color: #f2f2f2;
			}
		}
	}
}
.flip-effect.top {
	.info-box {
		z-index: 1;
		background: @xf-xrImageHoverEffectColor;
		-webkit-transform: translateZ(0) rotateX(-180deg);
		-moz-transform: translateZ(0) rotateX(-180deg);
		-ms-transform: translateZ(0) rotateX(-180deg);
		-o-transform: translateZ(0) rotateX(-180deg);
		transform: translateZ(0) rotateX(-180deg);
	}
	&:hover {
		.img-box {
			-webkit-transform: translateZ(0) rotateX(180deg);
			-moz-transform: translateZ(0) rotateX(180deg);
			-ms-transform: translateZ(0) rotateX(180deg);
			-o-transform: translateZ(0) rotateX(180deg);
			transform: translateZ(0) rotateX(180deg);
		}
		.info-box {
			-webkit-transform: translateZ(0) rotateX(0deg);
			-moz-transform: translateZ(0) rotateX(0deg);
			-ms-transform: translateZ(0) rotateX(0deg);
			-o-transform: translateZ(0) rotateX(0deg);
			transform: translateZ(0) rotateX(0deg);
		}
	}
}
.flip-effect.bottom {
	.info-box {
		z-index: 1;
		background: @xf-xrImageHoverEffectColor;
		-webkit-transform: translateZ(0) rotateX(180deg);
		-moz-transform: translateZ(0) rotateX(180deg);
		-ms-transform: translateZ(0) rotateX(180deg);
		-o-transform: translateZ(0) rotateX(180deg);
		transform: translateZ(0) rotateX(180deg);
	}
	&:hover {
		.img-box {
			-webkit-transform: translateZ(0) rotateX(-180deg);
			-moz-transform: translateZ(0) rotateX(-180deg);
			-ms-transform: translateZ(0) rotateX(-180deg);
			-o-transform: translateZ(0) rotateX(-180deg);
			transform: translateZ(0) rotateX(-180deg);
		}
		.info-box {
			-webkit-transform: translateZ(0) rotateX(0deg);
			-moz-transform: translateZ(0) rotateX(0deg);
			-ms-transform: translateZ(0) rotateX(0deg);
			-o-transform: translateZ(0) rotateX(0deg);
			transform: translateZ(0) rotateX(0deg);
		}
	}
}
.flip-effect.left {
	.info-box {
		z-index: 1;
		background: @xf-xrImageHoverEffectColor;
		-webkit-transform: translateZ(0) rotateY(180deg);
		-moz-transform: translateZ(0) rotateY(180deg);
		-ms-transform: translateZ(0) rotateY(180deg);
		-o-transform: translateZ(0) rotateY(180deg);
		transform: translateZ(0) rotateY(180deg);
	}
	&:hover {
		.img-box {
			-webkit-transform: translateZ(0) rotateY(-180deg);
			-moz-transform: translateZ(0) rotateY(-180deg);
			-ms-transform: translateZ(0) rotateY(-180deg);
			-o-transform: translateZ(0) rotateY(-180deg);
			transform: translateZ(0) rotateY(-180deg);
		}
		.info-box {
			-webkit-transform: translateZ(0) rotateY(0deg);
			-moz-transform: translateZ(0) rotateY(0deg);
			-ms-transform: translateZ(0) rotateY(0deg);
			-o-transform: translateZ(0) rotateY(0deg);
			transform: translateZ(0) rotateY(0deg);
		}
	}
}
.flip-effect.right {
	.info-box {
		z-index: 1;
		background: @xf-xrImageHoverEffectColor;
		-webkit-transform: translateZ(0) rotateY(-180deg);
		-moz-transform: translateZ(0) rotateY(-180deg);
		-ms-transform: translateZ(0) rotateY(-180deg);
		-o-transform: translateZ(0) rotateY(-180deg);
		transform: translateZ(0) rotateY(-180deg);
	}
	&:hover {
		.img-box {
			-webkit-transform: translateZ(0) rotateY(180deg);
			-moz-transform: translateZ(0) rotateY(180deg);
			-ms-transform: translateZ(0) rotateY(180deg);
			-o-transform: translateZ(0) rotateY(180deg);
			transform: translateZ(0) rotateY(180deg);
		}
		.info-box {
			-webkit-transform: translateZ(0) rotateY(0deg);
			-moz-transform: translateZ(0) rotateY(0deg);
			-ms-transform: translateZ(0) rotateY(0deg);
			-o-transform: translateZ(0) rotateY(0deg);
			transform: translateZ(0) rotateY(0deg);
		}
	}
}
.bubble-effect {
	display: block;
	position: relative;
	border-radius: 5px;
	box-shadow: 0 3px 15px -2px rgba(94,94,94,.65);
	-webkit-transform: translate3d(0, 0, 0);
	-moz-transform: translate3d(0, 0, 0);
	-ms-transform: translate3d(0, 0, 0);
	-o-transform: translate3d(0, 0, 0);
	transform: translate3d(0, 0, 0);
	.img-box {
		top: 0;
		right: 0;
		bottom: 0;
		left: 0;
		z-index: 1;
		a {
			color: #fff;
			&:active {
				color: #fff;
				&:hover {
					color: #f2f2f2;
				}
			}
			&:focus {
				color: #fff;
				&:hover {
					color: #f2f2f2;
				}
			}
			&:hover {
				color: #f2f2f2;
			}
		}
	}
	.info-box {
		top: 0;
		right: 0;
		bottom: 0;
		left: 0;
		z-index: 0;
		opacity: 0.85;
		background: @xf-xrImageHoverEffectColor;
		a {
			color: #fff;
			&:active {
				color: #fff;
				&:hover {
					color: #f2f2f2;
				}
			}
			&:focus {
				color: #fff;
				&:hover {
					color: #f2f2f2;
				}
			}
			&:hover {
				color: #f2f2f2;
			}
		}
	}
	.round {
		overflow: visible !important;
	}
}

.bubble-effect .img-box img:active:hover {
    border-radius: 10px;
}

.bubble-effect.top:hover .img-box img {
    border-radius: 10px;
}

.bubble-effect.round {
	overflow: visible !important;
}
.bubble-effect.top {
	&:hover {
		.img-box {
			z-index: 2;
			-webkit-transform: translateZ(0) translateY(-60%) scale(0.5, 0.5);
			-moz-transform: translateZ(0) translateY(-60%) scale(0.5, 0.5);
			-ms-transform: translateZ(0) translateY(-60%) scale(0.5, 0.5);
			-o-transform: translateZ(0) translateY(-60%) scale(0.5, 0.5);
			transform: translateZ(0) translateY(-60%) scale(0.5, 0.5);
		}
		.info-box {
			padding-top: 15%;
		}
	}
}
.bubble-effect.bottom {
	&:hover {
		.img-box {
			z-index: 2;
			-webkit-transform: translateZ(0) translateY(60%) scale(0.5, 0.5);
			-moz-transform: translateZ(0) translateY(60%) scale(0.5, 0.5);
			-ms-transform: translateZ(0) translateY(60%) scale(0.5, 0.5);
			-o-transform: translateZ(0) translateY(60%) scale(0.5, 0.5);
			transform: translateZ(0) translateY(60%) scale(0.5, 0.5);
		}
		.info-box {
			padding-bottom: 15%;
		}
	}
}
.bubble-effect.left {
	&:hover {
		.img-box {
			z-index: 2;
			-webkit-transform: translateZ(0) translateX(-60%) scale(0.5, 0.5);
			-moz-transform: translateZ(0) translateX(-60%) scale(0.5, 0.5);
			-ms-transform: translateZ(0) translateX(-60%) scale(0.5, 0.5);
			-o-transform: translateZ(0) translateX(-60%) scale(0.5, 0.5);
			transform: translateZ(0) translateX(-60%) scale(0.5, 0.5);
		}
		.info-box {
			padding-left: 15%;
		}
	}
}
.bubble-effect.right {
	&:hover {
		.img-box {
			z-index: 2;
			-webkit-transform: translateZ(0) translateX(60%) scale(0.5, 0.5);
			-moz-transform: translateZ(0) translateX(60%) scale(0.5, 0.5);
			-ms-transform: translateZ(0) translateX(60%) scale(0.5, 0.5);
			-o-transform: translateZ(0) translateX(60%) scale(0.5, 0.5);
			transform: translateZ(0) translateX(60%) scale(0.5, 0.5);
		}
		.info-box {
			padding-right: 15%;
		}
	}
}
.zoom-in-effect {
	display: block;
	overflow: hidden;
	border-radius: 5px;
	box-shadow: 0 3px 15px -2px rgba(94,94,94,.65);
	-webkit-transform: translate3d(0, 0, 0);
	-moz-transform: translate3d(0, 0, 0);
	-ms-transform: translate3d(0, 0, 0);
	-o-transform: translate3d(0, 0, 0);
	transform: translate3d(0, 0, 0);
	.img-box {
		top: 0;
		right: 0;
		bottom: 0;
		left: 0;
		color: #e6e6e6;
		z-index: 0;
		a {
			color: #fff;
			&:active {
				color: #fff;
				&:hover {
					color: #f2f2f2;
				}
			}
			&:focus {
				color: #fff;
				&:hover {
					color: #f2f2f2;
				}
			}
			&:hover {
				color: #f2f2f2;
			}
		}
	}
	.info-box {
		top: 0;
		right: 0;
		bottom: 0;
		left: 0;
		color: #e6e6e6;
		z-index: 1;
		background: @xf-xrImageHoverEffectColor;
		-webkit-transform: translateZ(0) scale(2, 2);
		-moz-transform: translateZ(0) scale(2, 2);
		-ms-transform: translateZ(0) scale(2, 2);
		-o-transform: translateZ(0) scale(2, 2);
		transform: translateZ(0) scale(2, 2);
		filter: alpha(opacity=0);
		-wekbit-opacity: 0;
		-moz-opacity: 0;
		opacity: 0;
		a {
			color: #fff;
			&:active {
				color: #fff;
				&:hover {
					color: #f2f2f2;
				}
			}
			&:focus {
				color: #fff;
				&:hover {
					color: #f2f2f2;
				}
			}
			&:hover {
				color: #f2f2f2;
			}
		}
	}
	&:hover {
		.img-box {
			-webkit-transform: translateZ(0) scale(1.1, 1.1);
			-moz-transform: translateZ(0) scale(1.1, 1.1);
			-ms-transform: translateZ(0) scale(1.1, 1.1);
			-o-transform: translateZ(0) scale(1.1, 1.1);
			transform: translateZ(0) scale(1.1, 1.1);
		}
		.info-box {
			-webkit-transform: translateZ(0) scale(1, 1);
			-moz-transform: translateZ(0) scale(1, 1);
			-ms-transform: translateZ(0) scale(1, 1);
			-o-transform: translateZ(0) scale(1, 1);
			transform: translateZ(0) scale(1, 1);
			filter: alpha(opacity=100);
			-wekbit-opacity: 1;
			-moz-opacity: 1;
			opacity: 0.85;
		}
	}
}
.square-spin-effect {
	display: block;
	overflow: hidden;
	position: relative;
	border-radius: 5px;
	box-shadow: 0 3px 15px -2px rgba(94,94,94,.65);
	-webkit-transform: translate3d(0, 0, 0);
	-moz-transform: translate3d(0, 0, 0);
	-ms-transform: translate3d(0, 0, 0);
	-o-transform: translate3d(0, 0, 0);
	transform: translate3d(0, 0, 0);
	.info-box {
		filter: alpha(opacity=0);
		-wekbit-opacity: 0;
		-moz-opacity: 0;
		opacity: 0;
		-webkit-transform: translateZ(0) scale(2, 2);
		-moz-transform: translateZ(0) scale(2, 2);
		-ms-transform: translateZ(0) scale(2, 2);
		-o-transform: translateZ(0) scale(2, 2);
		transform: translateZ(0) scale(2, 2);
		color: #e6e6e6;
		* {
			z-index: 3;
		}
		&:after {
			content: "";
			display: block !important;
			position: absolute;
			visibility: visible !important;
			background-color: rgba(0, 0, 0, 0.8);
			top: 0;
			left: 0;
			bottom: 0;
			right: 0;
			width: 100%;
			height: 100%;
			z-index: -1;
			-webkit-transition: 0.6s ease-in-out;
			-moz-transition: 0.6s ease-in-out;
			-ms-transition: 0.6s ease-in-out;
			-o-transition: 0.6s ease-in-out;
			transition: 0.6s ease-in-out;
		}
		&:before {
			content: "";
			display: block !important;
			position: absolute;
			visibility: visible !important;
			background-color: rgba(0, 0, 0, 0.8);
			top: 0;
			left: 0;
			bottom: 0;
			right: 0;
			width: 100%;
			height: 100%;
			z-index: -1;
			-webkit-transition: 0.6s ease-in-out;
			-moz-transition: 0.6s ease-in-out;
			-ms-transition: 0.6s ease-in-out;
			-o-transition: 0.6s ease-in-out;
			transition: 0.6s ease-in-out;
		}
	}
}
.square-spin-effect.vertical {
	.info-box {
		&:before {
			-webkit-transform: translateZ(0) translateX(100%) rotateZ(180deg);
			-moz-transform: translateZ(0) translateX(100%) rotateZ(180deg);
			-ms-transform: translateZ(0) translateX(100%) rotateZ(180deg);
			-o-transform: translateZ(0) translateX(100%) rotateZ(180deg);
			transform: translateZ(0) translateX(100%) rotateZ(180deg);
		}
		&:after {
			-webkit-transform: translateZ(0) translateX(-100%) rotateZ(180deg);
			-moz-transform: translateZ(0) translateX(-100%) rotateZ(180deg);
			-ms-transform: translateZ(0) translateX(-100%) rotateZ(180deg);
			-o-transform: translateZ(0) translateX(-100%) rotateZ(180deg);
			transform: translateZ(0) translateX(-100%) rotateZ(180deg);
		}
	}
	&:hover {
		.info-box {
			filter: alpha(opacity=100);
			-wekbit-opacity: 1;
			-moz-opacity: 1;
			opacity: 1;
			-webkit-transform: translateZ(0) scale(1, 1);
			-moz-transform: translateZ(0) scale(1, 1);
			-ms-transform: translateZ(0) scale(1, 1);
			-o-transform: translateZ(0) scale(1, 1);
			transform: translateZ(0) scale(1, 1);
			&:before {
				-webkit-transform: translateZ(0) translateX(50%) rotateZ(0deg);
				-moz-transform: translateZ(0) translateX(50%) rotateZ(0deg);
				-ms-transform: translateZ(0) translateX(50%) rotateZ(0deg);
				-o-transform: translateZ(0) translateX(50%) rotateZ(0deg);
				transform: translateZ(0) translateX(50%) rotateZ(0deg);
			}
			&:after {
				-webkit-transform: translateZ(0) translateX(-50%) rotateZ(0deg);
				-moz-transform: translateZ(0) translateX(-50%) rotateZ(0deg);
				-ms-transform: translateZ(0) translateX(-50%) rotateZ(0deg);
				-o-transform: translateZ(0) translateX(-50%) rotateZ(0deg);
				transform: translateZ(0) translateX(-50%) rotateZ(0deg);
			}
		}
	}
}
.square-spin-effect.horizontal {
	.info-box {
		&:before {
			-webkit-transform: translateZ(0) translateY(100%) rotateZ(180deg);
			-moz-transform: translateZ(0) translateY(100%) rotateZ(180deg);
			-ms-transform: translateZ(0) translateY(100%) rotateZ(180deg);
			-o-transform: translateZ(0) translateY(100%) rotateZ(180deg);
			transform: translateZ(0) translateY(100%) rotateZ(180deg);
		}
		&:after {
			-webkit-transform: translateZ(0) translateY(-100%) rotateZ(180deg);
			-moz-transform: translateZ(0) translateY(-100%) rotateZ(180deg);
			-ms-transform: translateZ(0) translateY(-100%) rotateZ(180deg);
			-o-transform: translateZ(0) translateY(-100%) rotateZ(180deg);
			transform: translateZ(0) translateY(-100%) rotateZ(180deg);
		}
	}
	&:hover {
		.info-box {
			filter: alpha(opacity=100);
			-wekbit-opacity: 1;
			-moz-opacity: 1;
			opacity: 1;
			-webkit-transform: translateZ(0) scale(1, 1);
			-moz-transform: translateZ(0) scale(1, 1);
			-ms-transform: translateZ(0) scale(1, 1);
			-o-transform: translateZ(0) scale(1, 1);
			transform: translateZ(0) scale(1, 1);
			&:before {
				-webkit-transform: translateZ(0) translateY(50%) rotateZ(0deg);
				-moz-transform: translateZ(0) translateY(50%) rotateZ(0deg);
				-ms-transform: translateZ(0) translateY(50%) rotateZ(0deg);
				-o-transform: translateZ(0) translateY(50%) rotateZ(0deg);
				transform: translateZ(0) translateY(50%) rotateZ(0deg);
			}
			&:after {
				-webkit-transform: translateZ(0) translateY(-50%) rotateZ(0deg);
				-moz-transform: translateZ(0) translateY(-50%) rotateZ(0deg);
				-ms-transform: translateZ(0) translateY(-50%) rotateZ(0deg);
				-o-transform: translateZ(0) translateY(-50%) rotateZ(0deg);
				transform: translateZ(0) translateY(-50%) rotateZ(0deg);
			}
		}
	}
}
.over-flip-effect {
	display: block;
	position: relative;
	border-radius: 5px;
	box-shadow: 0 3px 15px -2px rgba(94,94,94,.65);
	-webkit-perspective: 1000px;
	-moz-perspective: 1000px;
	-ms-perspective: 1000px;
	-o-perspective: 1000px;
	perspective: 1000px;
	-webkit-transform: translate3d(0, 0, 0);
	-moz-transform: translate3d(0, 0, 0);
	-ms-transform: translate3d(0, 0, 0);
	-o-transform: translate3d(0, 0, 0);
	transform: translate3d(0, 0, 0);
	.img-box {
		display: block;
		width: 100%;
		height: 100%;
		-webkit-transition: all 0.5s ease-in-out;
		-moz-transition: all 0.5s ease-in-out;
		-ms-transition: all 0.5s ease-in-out;
		-o-transition: all 0.5s ease-in-out;
		transition: all 0.5s ease-in-out;
		-webkit-transform-style: preserve-3d;
		-moz-transform-style: preserve-3d;
		-ms-transform-style: preserve-3d;
		-o-transform-style: preserve-3d;
		transform-style: preserve-3d;
		-webkit-transform-origin: center center right;
		-moz-transform-origin: center center right;
		-ms-transform-origin: center center right;
		-o-transform-origin: center center right;
		transform-origin: center center right;
		-webkit-box-sizing: border-box;
		-moz-box-sizing: border-box;
		-ms-box-sizing: border-box;
		-o-box-sizing: border-box;
		box-sizing: border-box;
		z-index: 2;
	}
	.info-box {
		display: block;
		width: 100%;
		height: 100%;
		-webkit-transition: all 0.5s ease-in-out;
		-moz-transition: all 0.5s ease-in-out;
		-ms-transition: all 0.5s ease-in-out;
		-o-transition: all 0.5s ease-in-out;
		transition: all 0.5s ease-in-out;
		-webkit-transform-style: preserve-3d;
		-moz-transform-style: preserve-3d;
		-ms-transform-style: preserve-3d;
		-o-transform-style: preserve-3d;
		transform-style: preserve-3d;
		-webkit-transform-origin: center center right;
		-moz-transform-origin: center center right;
		-ms-transform-origin: center center right;
		-o-transform-origin: center center right;
		transform-origin: center center right;
		-webkit-box-sizing: border-box;
		-moz-box-sizing: border-box;
		-ms-box-sizing: border-box;
		-o-box-sizing: border-box;
		box-sizing: border-box;
		opacity: 0.85;
		background: @xf-xrImageHoverEffectColor;
		z-index: 1;
		position: absolute;
	}
}
.over-flip-effect.top {
	.info-box {
		-webkit-transform: rotateX(-90deg);
		-moz-transform: rotateX(-90deg);
		-ms-transform: rotateX(-90deg);
		-o-transform: rotateX(-90deg);
		transform: rotateX(-90deg);
	}
	&:hover {
		.img-box {
			-webkit-transform: rotateX(90deg);
			-moz-transform: rotateX(90deg);
			-ms-transform: rotateX(90deg);
			-o-transform: rotateX(90deg);
			transform: rotateX(90deg);
		}
		.info-box {
			-webkit-transform: rotateX(0deg);
			-moz-transform: rotateX(0deg);
			-ms-transform: rotateX(0deg);
			-o-transform: rotateX(0deg);
			transform: rotateX(0deg);
		}
	}
}
.over-flip-effect.bottom {
	.info-box {
		-webkit-transform: rotateX(90deg);
		-moz-transform: rotateX(90deg);
		-ms-transform: rotateX(90deg);
		-o-transform: rotateX(90deg);
		transform: rotateX(90deg);
	}
	&:hover {
		.img-box {
			-webkit-transform: rotateX(-90deg);
			-moz-transform: rotateX(-90deg);
			-ms-transform: rotateX(-90deg);
			-o-transform: rotateX(-90deg);
			transform: rotateX(-90deg);
		}
		.info-box {
			-webkit-transform: rotateX(0deg);
			-moz-transform: rotateX(0deg);
			-ms-transform: rotateX(0deg);
			-o-transform: rotateX(0deg);
			transform: rotateX(0deg);
		}
	}
}
.over-flip-effect.left {
	.info-box {
		-webkit-transform: rotateY(90deg);
		-moz-transform: rotateY(90deg);
		-ms-transform: rotateY(90deg);
		-o-transform: rotateY(90deg);
		transform: rotateY(90deg);
	}
	&:hover {
		.img-box {
			-webkit-transform: rotateY(-90deg);
			-moz-transform: rotateY(-90deg);
			-ms-transform: rotateY(-90deg);
			-o-transform: rotateY(-90deg);
			transform: rotateY(-90deg);
		}
		.info-box {
			-webkit-transform: rotateY(0deg);
			-moz-transform: rotateY(0deg);
			-ms-transform: rotateY(0deg);
			-o-transform: rotateY(0deg);
			transform: rotateY(0deg);
		}
	}
}
.over-flip-effect.right {
	.info-box {
		-webkit-transform: rotateY(-90deg);
		-moz-transform: rotateY(-90deg);
		-ms-transform: rotateY(-90deg);
		-o-transform: rotateY(-90deg);
		transform: rotateY(-90deg);
	}
	&:hover {
		.img-box {
			-webkit-transform: rotateY(90deg);
			-moz-transform: rotateY(90deg);
			-ms-transform: rotateY(90deg);
			-o-transform: rotateY(90deg);
			transform: rotateY(90deg);
		}
		.info-box {
			-webkit-transform: rotateY(0deg);
			-moz-transform: rotateY(0deg);
			-ms-transform: rotateY(0deg);
			-o-transform: rotateY(0deg);
			transform: rotateY(0deg);
		}
	}
}
.rotate-switch-effect {
	display: block;
	position: relative;
	border-radius: 5px;
	box-shadow: 0 3px 15px -2px rgba(94,94,94,.65);
	-webkit-transform: translate3d(0, 0, 0);
	-moz-transform: translate3d(0, 0, 0);
	-ms-transform: translate3d(0, 0, 0);
	-o-transform: translate3d(0, 0, 0);
	transform: translate3d(0, 0, 0);
	.info-box {
		background-color: rgba(0, 0, 0, 0.6);
		-webkit-transform: rotateZ(360deg) scale(0, 0);
		-moz-transform: rotateZ(360deg) scale(0, 0);
		-ms-transform: rotateZ(360deg) scale(0, 0);
		-o-transform: rotateZ(360deg) scale(0, 0);
		transform: rotateZ(360deg) scale(0, 0);
	}
	.img-box {
		-webkit-transform: rotateZ(0) scale(1, 1);
		-moz-transform: rotateZ(0) scale(1, 1);
		-ms-transform: rotateZ(0) scale(1, 1);
		-o-transform: rotateZ(0) scale(1, 1);
		transform: rotateZ(0) scale(1, 1);
	}
	&:hover {
		.info-box {
			-webkit-transform: rotateZ(0) scale(1, 1);
			-moz-transform: rotateZ(0) scale(1, 1);
			-ms-transform: rotateZ(0) scale(1, 1);
			-o-transform: rotateZ(0) scale(1, 1);
			transform: rotateZ(0) scale(1, 1);
		}
		.img-box {
			-webkit-transform: rotateZ(-360deg) scale(0, 0);
			-moz-transform: rotateZ(-360deg) scale(0, 0);
			-ms-transform: rotateZ(-360deg) scale(0, 0);
			-o-transform: rotateZ(-360deg) scale(0, 0);
			transform: rotateZ(-360deg) scale(0, 0);
			z-index: 0;
		}
	}
}
.grid-reveal-effect {
	display: block;
	position: relative;
	border-radius: 5px;
	box-shadow: 0 3px 15px -2px rgba(94,94,94,.65);
	-webkit-transform: translate3d(0, 0, 0);
	-moz-transform: translate3d(0, 0, 0);
	-ms-transform: translate3d(0, 0, 0);
	-o-transform: translate3d(0, 0, 0);
	transform: translate3d(0, 0, 0);
	-webkit-transition: all 0.6s ease-in-out;
	-moz-transition: all 0.6s ease-in-out;
	-ms-transition: all 0.6s ease-in-out;
	-o-transition: all 0.6s ease-in-out;
	transition: all 0.6s ease-in-out;
	overflow: hidden;
	.info-content {
		z-index: 2 !important;
		filter: alpha(opacity=0);
		-wekbit-opacity: 0;
		-moz-opacity: 0;
		opacity: 0;
		-webkit-transition: all 0.5s ease-in-out;
		-moz-transition: all 0.5s ease-in-out;
		-ms-transition: all 0.5s ease-in-out;
		-o-transition: all 0.5s ease-in-out;
		transition: all 0.5s ease-in-out;
	}
	.img-box {
		&:after {
			content: "";
			display: block;
			position: absolute;
			background-color: rgba(0, 0, 0, 0.8);
			z-index: 1;
			-webkit-transition: 0.8s ease-in-out;
			-moz-transition: 0.8s ease-in-out;
			-ms-transition: 0.8s ease-in-out;
			-o-transition: 0.8s ease-in-out;
			transition: 0.8s ease-in-out;
			filter: alpha(opacity=0);
			-wekbit-opacity: 0;
			-moz-opacity: 0;
			opacity: 0;
		}
		&:before {
			content: "";
			display: block;
			position: absolute;
			background-color: rgba(0, 0, 0, 0.8);
			z-index: 1;
			-webkit-transition: 0.8s ease-in-out;
			-moz-transition: 0.8s ease-in-out;
			-ms-transition: 0.8s ease-in-out;
			-o-transition: 0.8s ease-in-out;
			transition: 0.8s ease-in-out;
			filter: alpha(opacity=0);
			-wekbit-opacity: 0;
			-moz-opacity: 0;
			opacity: 0;
		}
	}
	.info-box {
		&:after {
			content: "";
			display: block;
			position: absolute;
			background-color: rgba(0, 0, 0, 0.8);
			z-index: 1;
			-webkit-transition: 0.8s ease-in-out;
			-moz-transition: 0.8s ease-in-out;
			-ms-transition: 0.8s ease-in-out;
			-o-transition: 0.8s ease-in-out;
			transition: 0.8s ease-in-out;
			filter: alpha(opacity=0);
			-wekbit-opacity: 0;
			-moz-opacity: 0;
			opacity: 0;
		}
		&:before {
			content: "";
			display: block;
			position: absolute;
			background-color: rgba(0, 0, 0, 0.8);
			z-index: 1;
			-webkit-transition: 0.8s ease-in-out;
			-moz-transition: 0.8s ease-in-out;
			-ms-transition: 0.8s ease-in-out;
			-o-transition: 0.8s ease-in-out;
			transition: 0.8s ease-in-out;
			filter: alpha(opacity=0);
			-wekbit-opacity: 0;
			-moz-opacity: 0;
			opacity: 0;
		}
	}
	&:hover {
		.img-box {
			&:after {
				-webkit-transform: rotateX(0deg);
				-moz-transform: rotateX(0deg);
				-ms-transform: rotateX(0deg);
				-o-transform: rotateX(0deg);
				transform: rotateX(0deg);
				filter: alpha(opacity=100);
				-wekbit-opacity: 1;
				-moz-opacity: 1;
				opacity: 1;
			}
			&:before {
				-webkit-transform: rotateX(0deg);
				-moz-transform: rotateX(0deg);
				-ms-transform: rotateX(0deg);
				-o-transform: rotateX(0deg);
				transform: rotateX(0deg);
				filter: alpha(opacity=100);
				-wekbit-opacity: 1;
				-moz-opacity: 1;
				opacity: 1;
			}
		}
		.info-box {
			&:after {
				-webkit-transform: rotateX(0deg);
				-moz-transform: rotateX(0deg);
				-ms-transform: rotateX(0deg);
				-o-transform: rotateX(0deg);
				transform: rotateX(0deg);
				filter: alpha(opacity=100);
				-wekbit-opacity: 1;
				-moz-opacity: 1;
				opacity: 1;
			}
			&:before {
				-webkit-transform: rotateX(0deg);
				-moz-transform: rotateX(0deg);
				-ms-transform: rotateX(0deg);
				-o-transform: rotateX(0deg);
				transform: rotateX(0deg);
				filter: alpha(opacity=100);
				-wekbit-opacity: 1;
				-moz-opacity: 1;
				opacity: 1;
			}
		}
		.info-content {
			filter: alpha(opacity=100);
			-wekbit-opacity: 1;
			-moz-opacity: 1;
			opacity: 1;
		}
	}
}
.grid-reveal-effect.horizontal {
	.img-box {
		&:before {
			top: 0;
			left: 0;
			width: 100%;
			height: 25%;
			-webkit-transform: rotateX(90deg);
			-moz-transform: rotateX(90deg);
			-ms-transform: rotateX(90deg);
			-o-transform: rotateX(90deg);
			transform: rotateX(90deg);
		}
		&:after {
			top: 25%;
			left: 0;
			width: 100%;
			height: 25%;
			-webkit-transform: rotateX(90deg);
			-moz-transform: rotateX(90deg);
			-ms-transform: rotateX(90deg);
			-o-transform: rotateX(90deg);
			transform: rotateX(90deg);
		}
	}
	.info-box {
		&:after {
			top: 50%;
			left: 0;
			width: 100%;
			height: 25%;
			-webkit-transform: rotateX(90deg);
			-moz-transform: rotateX(90deg);
			-ms-transform: rotateX(90deg);
			-o-transform: rotateX(90deg);
			transform: rotateX(90deg);
		}
		&:before {
			top: 75%;
			left: 0;
			width: 100%;
			height: calc(25% + 1px);
			-webkit-transform: rotateX(90deg);
			-moz-transform: rotateX(90deg);
			-ms-transform: rotateX(90deg);
			-o-transform: rotateX(90deg);
			transform: rotateX(90deg);
		}
	}
}
.grid-reveal-effect.vertical {
	.img-box {
		&:before {
			top: 0;
			left: 0;
			width: 25%;
			height: 100%;
			-webkit-transform: rotateY(90deg);
			-moz-transform: rotateY(90deg);
			-ms-transform: rotateY(90deg);
			-o-transform: rotateY(90deg);
			transform: rotateY(90deg);
		}
		&:after {
			top: 0;
			left: 25%;
			width: 25%;
			height: 100%;
			-webkit-transform: rotateY(90deg);
			-moz-transform: rotateY(90deg);
			-ms-transform: rotateY(90deg);
			-o-transform: rotateY(90deg);
			transform: rotateY(90deg);
		}
	}
	.info-box {
		&:after {
			top: 0;
			left: 50%;
			width: 25%;
			height: 100%;
			-webkit-transform: rotateY(90deg);
			-moz-transform: rotateY(90deg);
			-ms-transform: rotateY(90deg);
			-o-transform: rotateY(90deg);
			transform: rotateY(90deg);
		}
		&:before {
			top: 0;
			left: 75%;
			width: calc(25% + 1px);
			height: 100%;
			-webkit-transform: rotateY(90deg);
			-moz-transform: rotateY(90deg);
			-ms-transform: rotateY(90deg);
			-o-transform: rotateY(90deg);
			transform: rotateY(90deg);
		}
	}
}
.swipe-effect {
	display: block;
	overflow: hidden;
	position: relative;
	border-radius: 5px;
	box-shadow: 0 3px 15px -2px rgba(94,94,94,.65);
	-webkit-transform: translate3d(0, 0, 0);
	-moz-transform: translate3d(0, 0, 0);
	-ms-transform: translate3d(0, 0, 0);
	-o-transform: translate3d(0, 0, 0);
	transform: translate3d(0, 0, 0);
	.info-box {
		.info-content {
			z-index: 2;
			filter: alpha(opacity=0);
			-wekbit-opacity: 0;
			-moz-opacity: 0;
			opacity: 0;
			-webkit-transition: all 0.5s ease-in-out;
			-moz-transition: all 0.5s ease-in-out;
			-ms-transition: all 0.5s ease-in-out;
			-o-transition: all 0.5s ease-in-out;
			transition: all 0.5s ease-in-out;
		}
		&:before {
			content: \'\';
			display: block;
			position: absolute;
			width: 210%;
			height: 30%;
			z-index: 1;
			left: 115%;
			top: -10%;
			-webkit-transform: translate3d(-50%, -50%, 0) rotateZ(45deg);
			-moz-transform: translate3d(-50%, -50%, 0) rotateZ(45deg);
			-ms-transform: translate3d(-50%, -50%, 0) rotateZ(45deg);
			-o-transform: translate3d(-50%, -50%, 0) rotateZ(45deg);
			transform: translate3d(-50%, -50%, 0) rotateZ(45deg);
			background-color: rgba(255, 255, 255, 0.1);
			-webkit-transition: all 0.8s ease-in-out;
			-moz-transition: all 0.8s ease-in-out;
			-ms-transition: all 0.8s ease-in-out;
			-o-transition: all 0.8s ease-in-out;
			transition: all 0.8s ease-in-out;
		}
		&:after {
			content: \'\';
			display: block;
			position: absolute;
			width: 210%;
			height: 30%;
			z-index: 1;
			left: 115%;
			top: -10%;
			-webkit-transform: translate3d(-50%, -50%, 0) rotateZ(45deg);
			-moz-transform: translate3d(-50%, -50%, 0) rotateZ(45deg);
			-ms-transform: translate3d(-50%, -50%, 0) rotateZ(45deg);
			-o-transform: translate3d(-50%, -50%, 0) rotateZ(45deg);
			transform: translate3d(-50%, -50%, 0) rotateZ(45deg);
			background-color: rgba(255, 255, 255, 0.05);
			-webkit-transition: all 1.1s ease-in-out;
			-moz-transition: all 1.1s ease-in-out;
			-ms-transition: all 1.1s ease-in-out;
			-o-transition: all 1.1s ease-in-out;
			transition: all 1.1s ease-in-out;
		}
	}
	.img-box {
		&:before {
			content: \'\';
			display: block;
			position: absolute;
			width: 100%;
			height: 100%;
			background-color: rgba(0, 0, 0, 0.7);
			z-index: 1;
			filter: alpha(opacity=0);
			-wekbit-opacity: 0;
			-moz-opacity: 0;
			opacity: 0;
			-webkit-transition: all 0.5s ease-in-out;
			-moz-transition: all 0.5s ease-in-out;
			-ms-transition: all 0.5s ease-in-out;
			-o-transition: all 0.5s ease-in-out;
			transition: all 0.5s ease-in-out;
		}
	}
	&:hover {
		.img-box {
			&:before {
				filter: alpha(opacity=100);
				-wekbit-opacity: 1;
				-moz-opacity: 1;
				opacity: 1;
			}
		}
		.info-content {
			filter: alpha(opacity=100);
			-wekbit-opacity: 1;
			-moz-opacity: 1;
			opacity: 1;
		}
		.info-box {
			&:before {
				left: -100%;
				top: 210%;
				height: 220%;
			}
			&:after {
				left: -100%;
				top: 210%;
				height: 100%;
			}
		}
	}
}
.flip-back-effect {
	display: block;
	position: relative;
	border-radius: 5px;
	box-shadow: 0 3px 15px -2px rgba(94,94,94,.65);
	-webkit-transform: translate3d(0, 0, 0);
	-moz-transform: translate3d(0, 0, 0);
	-ms-transform: translate3d(0, 0, 0);
	-o-transform: translate3d(0, 0, 0);
	transform: translate3d(0, 0, 0);
	-webkit-perspective: 800px;
	-moz-perspective: 800px;
	-ms-perspective: 800px;
	-o-perspective: 800px;
	perspective: 800px;
	-webkit-transform-style: preserve3d;
	-moz-transform-style: preserve3d;
	-ms-transform-style: preserve3d;
	-o-transform-style: preserve3d;
	transform-style: preserve3d;
	.img-box {
		z-index: 1;
	}
	.info-box {
		opacity: 0.85;
		background: @xf-xrImageHoverEffectColor;
		z-index: 0;
	}
	&:hover {
		.img-box {
			-webkit-transition: 0.6s;
			-moz-transition: 0.6s;
			-ms-transition: 0.6s;
			-o-transition: 0.6s;
			transition: 0.6s;
			filter: alpha(opacity=0);
			-wekbit-opacity: 0;
			-moz-opacity: 0;
			opacity: 0;
		}
	}
	&:hover.top {
		.img-box {
			-webkit-transform: translateY(-100%) rotateX(90deg);
			-moz-transform: translateY(-100%) rotateX(90deg);
			-ms-transform: translateY(-100%) rotateX(90deg);
			-o-transform: translateY(-100%) rotateX(90deg);
			transform: translateY(-100%) rotateX(90deg);
			-webkit-transform-origin: bottom;
			-moz-transform-origin: bottom;
			-ms-transform-origin: bottom;
			-o-transform-origin: bottom;
			transform-origin: bottom;
		}
	}
	&:hover.right {
		.img-box {
			-webkit-transform: translateX(100%) rotateY(90deg);
			-moz-transform: translateX(100%) rotateY(90deg);
			-ms-transform: translateX(100%) rotateY(90deg);
			-o-transform: translateX(100%) rotateY(90deg);
			transform: translateX(100%) rotateY(90deg);
			-webkit-transform-origin: left;
			-moz-transform-origin: left;
			-ms-transform-origin: left;
			-o-transform-origin: left;
			transform-origin: left;
		}
	}
	&:hover.bottom {
		.img-box {
			-webkit-transform: translateY(100%) rotateX(-90deg);
			-moz-transform: translateY(100%) rotateX(-90deg);
			-ms-transform: translateY(100%) rotateX(-90deg);
			-o-transform: translateY(100%) rotateX(-90deg);
			transform: translateY(100%) rotateX(-90deg);
			-webkit-transform-origin: top;
			-moz-transform-origin: top;
			-ms-transform-origin: top;
			-o-transform-origin: top;
			transform-origin: top;
		}
	}
	&:hover.left {
		.img-box {
			-webkit-transform: translateX(-100%) rotateY(-90deg);
			-moz-transform: translateX(-100%) rotateY(-90deg);
			-ms-transform: translateX(-100%) rotateY(-90deg);
			-o-transform: translateX(-100%) rotateY(-90deg);
			transform: translateX(-100%) rotateY(-90deg);
			-webkit-transform-origin: right;
			-moz-transform-origin: right;
			-ms-transform-origin: right;
			-o-transform-origin: right;
			transform-origin: right;
		}
	}
}
.switch-3d-effect {
	display: block;
	position: relative;
	border-radius: 5px;
	box-shadow: 0 3px 15px -2px rgba(94,94,94,.65);
	-webkit-transform: translate3d(0, 0, 0);
	-moz-transform: translate3d(0, 0, 0);
	-ms-transform: translate3d(0, 0, 0);
	-o-transform: translate3d(0, 0, 0);
	transform: translate3d(0, 0, 0);
	-webkit-perspective: 800px;
	-moz-perspective: 800px;
	-ms-perspective: 800px;
	-o-perspective: 800px;
	perspective: 800px;
	-webkit-transform-style: preserve3d;
	-moz-transform-style: preserve3d;
	-ms-transform-style: preserve3d;
	-o-transform-style: preserve3d;
	transform-style: preserve3d;
	.img-box {
		z-index: 1;
	}
	.info-box {
		background: rgba(0, 0, 0, 0.6);
		z-index: 0;
		filter: alpha(opacity=0);
		-wekbit-opacity: 0;
		-moz-opacity: 0;
		opacity: 0;
	}
	&:hover {
		.img-box {
			-webkit-transition: 0.6s;
			-moz-transition: 0.6s;
			-ms-transition: 0.6s;
			-o-transition: 0.6s;
			transition: 0.6s;
			filter: alpha(opacity=0);
			-wekbit-opacity: 0;
			-moz-opacity: 0;
			opacity: 0;
		}
	}
	&:hover.top {
		.img-box {
			-webkit-transform: translateY(-100%) rotateX(90deg);
			-moz-transform: translateY(-100%) rotateX(90deg);
			-ms-transform: translateY(-100%) rotateX(90deg);
			-o-transform: translateY(-100%) rotateX(90deg);
			transform: translateY(-100%) rotateX(90deg);
			-webkit-transform-origin: bottom;
			-moz-transform-origin: bottom;
			-ms-transform-origin: bottom;
			-o-transform-origin: bottom;
			transform-origin: bottom;
		}
		.info-box {
			-webkit-transform: translateY(0) rotateX(0);
			-moz-transform: translateY(0) rotateX(0);
			-ms-transform: translateY(0) rotateX(0);
			-o-transform: translateY(0) rotateX(0);
			transform: translateY(0) rotateX(0);
			-webkit-transform-origin: bottom;
			-moz-transform-origin: bottom;
			-ms-transform-origin: bottom;
			-o-transform-origin: bottom;
			transform-origin: bottom;
			filter: alpha(opacity=100);
			-wekbit-opacity: 1;
			-moz-opacity: 1;
			opacity: 1;
		}
	}
	&:hover.right {
		.img-box {
			-webkit-transform: translateX(100%) rotateY(90deg);
			-moz-transform: translateX(100%) rotateY(90deg);
			-ms-transform: translateX(100%) rotateY(90deg);
			-o-transform: translateX(100%) rotateY(90deg);
			transform: translateX(100%) rotateY(90deg);
			-webkit-transform-origin: left;
			-moz-transform-origin: left;
			-ms-transform-origin: left;
			-o-transform-origin: left;
			transform-origin: left;
		}
		.info-box {
			-webkit-transform: translateY(0) rotateX(0);
			-moz-transform: translateY(0) rotateX(0);
			-ms-transform: translateY(0) rotateX(0);
			-o-transform: translateY(0) rotateX(0);
			transform: translateY(0) rotateX(0);
			-webkit-transform-origin: bottom;
			-moz-transform-origin: bottom;
			-ms-transform-origin: bottom;
			-o-transform-origin: bottom;
			transform-origin: bottom;
			filter: alpha(opacity=100);
			-wekbit-opacity: 1;
			-moz-opacity: 1;
			opacity: 1;
		}
	}
	&:hover.bottom {
		.img-box {
			-webkit-transform: translateY(100%) rotateX(-90deg);
			-moz-transform: translateY(100%) rotateX(-90deg);
			-ms-transform: translateY(100%) rotateX(-90deg);
			-o-transform: translateY(100%) rotateX(-90deg);
			transform: translateY(100%) rotateX(-90deg);
			-webkit-transform-origin: top;
			-moz-transform-origin: top;
			-ms-transform-origin: top;
			-o-transform-origin: top;
			transform-origin: top;
		}
		.info-box {
			-webkit-transform: translateY(0) rotateX(0);
			-moz-transform: translateY(0) rotateX(0);
			-ms-transform: translateY(0) rotateX(0);
			-o-transform: translateY(0) rotateX(0);
			transform: translateY(0) rotateX(0);
			-webkit-transform-origin: bottom;
			-moz-transform-origin: bottom;
			-ms-transform-origin: bottom;
			-o-transform-origin: bottom;
			transform-origin: bottom;
			filter: alpha(opacity=100);
			-wekbit-opacity: 1;
			-moz-opacity: 1;
			opacity: 1;
		}
	}
	&:hover.left {
		.img-box {
			-webkit-transform: translateX(-100%) rotateY(-90deg);
			-moz-transform: translateX(-100%) rotateY(-90deg);
			-ms-transform: translateX(-100%) rotateY(-90deg);
			-o-transform: translateX(-100%) rotateY(-90deg);
			transform: translateX(-100%) rotateY(-90deg);
			-webkit-transform-origin: right;
			-moz-transform-origin: right;
			-ms-transform-origin: right;
			-o-transform-origin: right;
			transform-origin: right;
		}
		.info-box {
			-webkit-transform: translateY(0) rotateX(0);
			-moz-transform: translateY(0) rotateX(0);
			-ms-transform: translateY(0) rotateX(0);
			-o-transform: translateY(0) rotateX(0);
			transform: translateY(0) rotateX(0);
			-webkit-transform-origin: bottom;
			-moz-transform-origin: bottom;
			-ms-transform-origin: bottom;
			-o-transform-origin: bottom;
			transform-origin: bottom;
			filter: alpha(opacity=100);
			-wekbit-opacity: 1;
			-moz-opacity: 1;
			opacity: 1;
		}
	}
}
.switch-3d-effect.top {
	.info-box {
		-webkit-transform: translateY(-50%) rotateX(90deg);
		-moz-transform: translateY(-50%) rotateX(90deg);
		-ms-transform: translateY(-50%) rotateX(90deg);
		-o-transform: translateY(-50%) rotateX(90deg);
		transform: translateY(-50%) rotateX(90deg);
	}
}
.switch-3d-effect.right {
	.info-box {
		-webkit-transform: translateX(50%) rotateY(90deg);
		-moz-transform: translateX(50%) rotateY(90deg);
		-ms-transform: translateX(50%) rotateY(90deg);
		-o-transform: translateX(50%) rotateY(90deg);
		transform: translateX(50%) rotateY(90deg);
	}
}
.switch-3d-effect.bottom {
	.info-box {
		-webkit-transform: translateY(50%) rotateX(-90deg);
		-moz-transform: translateY(50%) rotateX(-90deg);
		-ms-transform: translateY(50%) rotateX(-90deg);
		-o-transform: translateY(50%) rotateX(-90deg);
		transform: translateY(50%) rotateX(-90deg);
	}
}
.switch-3d-effect.left {
	.info-box {
		-webkit-transform: translateX(-50%) rotateY(-90deg);
		-moz-transform: translateX(-50%) rotateY(-90deg);
		-ms-transform: translateX(-50%) rotateY(-90deg);
		-o-transform: translateX(-50%) rotateY(-90deg);
		transform: translateX(-50%) rotateY(-90deg);
	}
}
.flip-forward-effect {
	display: block;
	position: relative;
	border-radius: 5px;
	box-shadow: 0 3px 15px -2px rgba(94,94,94,.65);
	-webkit-transform: translate3d(0, 0, 0);
	-moz-transform: translate3d(0, 0, 0);
	-ms-transform: translate3d(0, 0, 0);
	-o-transform: translate3d(0, 0, 0);
	transform: translate3d(0, 0, 0);
	-webkit-perspective: 800px;
	-moz-perspective: 800px;
	-ms-perspective: 800px;
	-o-perspective: 800px;
	perspective: 800px;
	-webkit-transform-style: preserve3d;
	-moz-transform-style: preserve3d;
	-ms-transform-style: preserve3d;
	-o-transform-style: preserve3d;
	transform-style: preserve3d;
	.img-box {
		z-index: 1;
	}
	.info-box {
		background: rgba(0, 0, 0, 0.6);
		z-index: 2;
		filter: alpha(opacity=0);
		-wekbit-opacity: 0;
		-moz-opacity: 0;
		opacity: 0;
	}
	&:hover {
		.info-box {
			-webkit-transition: 0.6s;
			-moz-transition: 0.6s;
			-ms-transition: 0.6s;
			-o-transition: 0.6s;
			transition: 0.6s;
			filter: alpha(opacity=100);
			-wekbit-opacity: 1;
			-moz-opacity: 1;
			opacity: 1;
			-webkit-transform: translateX(0) rotateY(0);
			-moz-transform: translateX(0) rotateY(0);
			-ms-transform: translateX(0) rotateY(0);
			-o-transform: translateX(0) rotateY(0);
			transform: translateX(0) rotateY(0);
		}
	}
}
.flip-forward-effect.top {
	.info-box {
		-webkit-transform: translateY(-100%) rotateX(90deg);
		-moz-transform: translateY(-100%) rotateX(90deg);
		-ms-transform: translateY(-100%) rotateX(90deg);
		-o-transform: translateY(-100%) rotateX(90deg);
		transform: translateY(-100%) rotateX(90deg);
		-webkit-transform-origin: bottom;
		-moz-transform-origin: bottom;
		-ms-transform-origin: bottom;
		-o-transform-origin: bottom;
		transform-origin: bottom;
	}
}
.flip-forward-effect.right {
	.info-box {
		-webkit-transform: translateX(100%) rotateY(90deg);
		-moz-transform: translateX(100%) rotateY(90deg);
		-ms-transform: translateX(100%) rotateY(90deg);
		-o-transform: translateX(100%) rotateY(90deg);
		transform: translateX(100%) rotateY(90deg);
		-webkit-transform-origin: left;
		-moz-transform-origin: left;
		-ms-transform-origin: left;
		-o-transform-origin: left;
		transform-origin: left;
	}
}
.flip-forward-effect.bottom {
	.info-box {
		-webkit-transform: translateY(100%) rotateX(-90deg);
		-moz-transform: translateY(100%) rotateX(-90deg);
		-ms-transform: translateY(100%) rotateX(-90deg);
		-o-transform: translateY(100%) rotateX(-90deg);
		transform: translateY(100%) rotateX(-90deg);
		-webkit-transform-origin: top;
		-moz-transform-origin: top;
		-ms-transform-origin: top;
		-o-transform-origin: top;
		transform-origin: top;
	}
}
.flip-forward-effect.left {
	.info-box {
		-webkit-transform: translateX(-100%) rotateY(-90deg);
		-moz-transform: translateX(-100%) rotateY(-90deg);
		-ms-transform: translateX(-100%) rotateY(-90deg);
		-o-transform: translateX(-100%) rotateY(-90deg);
		transform: translateX(-100%) rotateY(-90deg);
		-webkit-transform-origin: right;
		-moz-transform-origin: right;
		-ms-transform-origin: right;
		-o-transform-origin: right;
		transform-origin: right;
	}
}
.slow-zoom-effect {
	display: block;
	overflow: hidden;
	position: relative;
	border-radius: 5px;
	box-shadow: 0 3px 15px -2px rgba(94,94,94,.65);
	-webkit-transform: translate3d(0, 0, 0);
	-moz-transform: translate3d(0, 0, 0);
	-ms-transform: translate3d(0, 0, 0);
	-o-transform: translate3d(0, 0, 0);
	transform: translate3d(0, 0, 0);
	.img-box {
		z-index: 0;
		-webkit-transform: scale(1);
		-moz-transform: scale(1);
		-ms-transform: scale(1);
		-o-transform: scale(1);
		transform: scale(1);
		-webkit-transition: all 2.2s ease-in-out;
		-moz-transition: all 2.2s ease-in-out;
		-ms-transition: all 2.2s ease-in-out;
		-o-transition: all 2.2s ease-in-out;
		transition: all 2.2s ease-in-out;
	}
	.info-box {
		background: rgba(0, 0, 0, 0.6);
		z-index: 2;
		filter: alpha(opacity=0);
		-wekbit-opacity: 0;
		-moz-opacity: 0;
		opacity: 0;
		-webkit-transform: scale(1.3);
		-moz-transform: scale(1.3);
		-ms-transform: scale(1.3);
		-o-transform: scale(1.3);
		transform: scale(1.3);
	}
	&:hover {
		.img-box {
			-webkit-transform: scale(1.5);
			-moz-transform: scale(1.5);
			-ms-transform: scale(1.5);
			-o-transform: scale(1.5);
			transform: scale(1.5);
		}
		.info-box {
			filter: alpha(opacity=100);
			-wekbit-opacity: 1;
			-moz-opacity: 1;
			opacity: 1;
			-webkit-transform: scale(1);
			-moz-transform: scale(1);
			-ms-transform: scale(1);
			-o-transform: scale(1);
			transform: scale(1);
		}
	}
}';
	return $__finalCompiled;
});