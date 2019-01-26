<?php

// ################## THIS IS ONLY TOUCHED BY LEGACY TRANSACTIONS ##################

$dir = __DIR__;
require ($dir . '/src/XF.php');

XF::start($dir);
$app = XF::setupApp('XF\Pub\App');

$request = $app->request();
$response = $app->response();

$response->redirect('payment_callback.php');
$response->send($request);

/** @var \XF\Entity\PaymentProvider $provider */
$provider = $app->em()->find('XF:PaymentProvider', 'paypal');

if (!$provider)
{
	$response->httpCode(404)
		->body('Unknown payment provider.')
		->send($request);

	return;
}

/** @var \XR\PM\Payment\LegacyPayPal $handler */
$class = \XF::extendClass('XR\PM\Payment\LegacyPayPal');
$handler = new $class($provider->provider_id);

$state = $handler->setupCallback($request);
$state->legacy = true;

if (!$handler->validateCallback($state))
{
	$response->httpCode($state->httpCode ?: 403);
}
else if (!$handler->validateTransaction($state))
{
	// We generally don't need these to retry, so send a successful response.
	$response->httpCode($state->httpCode ?: 200);
}
else if (!$handler->validatePurchaseRequest($state)
	|| !$handler->validatePurchasableHandler($state)
	|| !$handler->validatePaymentProfile($state)
	|| !$handler->validatePurchaser($state)
)
{
	$response->httpCode($state->httpCode ?: 404);
}
else if (!$handler->validatePurchasableData($state)
	|| !$handler->validateCost($state)
)
{
	$response->httpCode($state->httpCode ?: 403);
}
else
{
	$handler->setProviderMetadata($state);
	$handler->getPaymentResult($state);
	$handler->completeTransaction($state);
}

if ($state->logType)
{
	$handler->log($state);
}

$response
	->body(htmlspecialchars($state->logMessage))
	->send($request);