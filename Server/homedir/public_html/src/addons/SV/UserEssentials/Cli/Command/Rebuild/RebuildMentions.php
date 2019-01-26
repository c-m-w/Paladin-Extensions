<?php

namespace SV\UserEssentials\Cli\Command\Rebuild;

use Symfony\Component\Console\Input\InputInterface;
use Symfony\Component\Console\Input\InputOption;
use Symfony\Component\Console\Output\OutputInterface;
use XF\Cli\Command\Rebuild\AbstractRebuildCommand;

class RebuildMentions extends AbstractRebuildCommand
{
    protected function getRebuildName()
    {
        return 'sv-mentions';
    }

    protected function getRebuildDescription()
    {
        return 'Rebuilds mention tracking.';
    }

    protected function getRebuildClass()
    {
        \XF::db()->logQueries(false); // need to limit memory usage

        return 'SV\UserEssentials:ContentMentionsAll';
    }

    protected function configureOptions()
    {
        $this->addOption(
            'start',
            null,
            InputOption::VALUE_REQUIRED,
            'Requires type to be set, handles ID\'s between start and end'
        );
        $this->addOption(
            'end',
            null,
            InputOption::VALUE_REQUIRED,
            'Requires type to be set, handles ID\'s between start and end'
        );
        $this->addOption(
            'type',
            null,
            InputOption::VALUE_REQUIRED,
            'Content type to rebuild mention tracking for. Default: all'
        );
        $this->addOption(
            'preload',
            null,
            InputOption::VALUE_NONE,
            'Preload content in batches, this is racy if users are able to edit content!'
        );
    }

    protected function getSlotName(array $params)
    {
        if (isset($params['start']))
        {
            return '-' . $params['type']. '-' .$params['start'];
        }

        return '';
    }

    protected function execute(InputInterface $input, OutputInterface $output)
    {
        $globalOptions = array_keys($this->getApplication()->getDefinition()->getOptions());
        $params = $input->getOptions();
        if (empty($params['type']))
        {
            unset($params['start']);
            unset($params['end']);
        }
        else
        {
            $params['types'] = [$params['type']];
        }

        foreach ($globalOptions AS $globalOption)
        {
            unset($params[$globalOption]);
        }

        $this->setupAndRunJob(
            'xfRebuildJob-' . $this->getRebuildName() . $this->getSlotName($params),
            $this->getRebuildClass(),
            $params, $output
        );

        return 0;
    }
}