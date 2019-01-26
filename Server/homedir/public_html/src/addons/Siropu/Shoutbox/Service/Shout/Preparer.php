<?php

namespace Siropu\Shoutbox\Service\Shout;

class Preparer extends \XF\Service\AbstractService
{
	protected $message;
	protected $bbCodeProcessor;
	protected $errors = [];
	protected $isValid = false;

	public function __construct(\XF\App $app)
	{
		parent::__construct($app);
	}
	public function prepare($message)
	{
		$this->message = $this->processMessage($message);

		if (empty($this->message))
          {
               $this->errors[] = \XF::phraseDeferred('please_enter_valid_message');
          }

		if (($maxLength = \XF::options()->siropuShoutboxShoutMaxLength) && utf8_strlen($this->message) > $maxLength)
		{
			$this->errors[] = \XF::phraseDeferred('please_enter_message_with_no_more_than_x_characters', ['count' => $maxLength]);
		}

		$rendered = $this->app->bbCode()->render($message, 'simpleHtml', 'siropu_shoutbox:prepare', null);

		if (!strlen(trim($rendered)))
		{
			$this->errors[] = \XF::phraseDeferred('please_enter_valid_message');
		}

		if (empty($this->errors))
		{
			$this->isValid = true;
		}
	}
	public function isValid()
	{
		return $this->isValid;
	}
	public function getMessage()
	{
		return $this->message;
	}
	public function getErrors()
	{
		return $this->errors;
	}
	public function getUserMentions()
	{
		return $this->bbCodeProcessor->getFilterer('mentions')->getMentionedUsers();
	}
	protected function processMessage($message)
	{
		if (!\XF::options()->siropuShoutboxAllowBBCodes)
		{
			return $this->app->stringFormatter()->stripBbCode($message);
		}

		$this->bbCodeProcessor = $this->getBbCodeProcessor();
		$bbCodeContainer       = $this->app->bbCode();

		return $this->bbCodeProcessor->render($message, $bbCodeContainer->parser(), $bbCodeContainer->rules('siropu_chat'));
	}
	protected function getBbCodeProcessor()
	{
		$bbCodeContainer = $this->app->bbCode();
		$bbCodeProcessor = $bbCodeContainer->processor();

		if (\XF::options()->siropuShoutboxAutolink)
		{
			$bbCodeProcessor->addProcessorAction('autolink', $bbCodeContainer->processorAction('autolink'));
		}

		$bbCodeProcessor->addProcessorAction('mentions', $bbCodeContainer->processorAction('mentions'));

		return $bbCodeProcessor;
	}
}
