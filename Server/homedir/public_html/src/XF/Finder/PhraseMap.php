<?php

namespace XF\Finder;

use XF\Mvc\Entity\Finder;

class PhraseMap extends Finder
{
	public function isPhraseState($states)
	{
		if (!is_array($states))
		{
			$states = [$states];
		}

		if ($states)
		{
			$allPresent = in_array('default', $states) && in_array('custom', $states) && in_array('inherited', $states);
			if (!$allPresent)
			{
				$expression = $this->expression(
					'IF(%1$s = 0, \'default\', IF(%1$s = %2$s, \'custom\', \'inherited\'))',
					'Phrase.language_id', 'language_id'
				);
				$this->where($expression, $states);
			}
		}

		return $this;
	}

	public function orderTitle($direction = 'ASC')
	{
		$expression = $this->expression('CONVERT (%s USING utf8)', 'title');
		$this->order($expression, $direction);

		return $this;
	}
}