<?php

namespace Andy\RegistrationCode\XF\Pub\Controller;

class Register extends XFCP_Register
{
	public function actionRegister()
	{
		$this->assertPostOnly();
		$this->assertRegistrationActive();
		
		// get options
		$options = \XF::options();

		// get options from Admin CP -> Options -> Registration code -> Registration code
		$registrationCode = $options->registrationCodeRegistrationCode;
		
		if ($registrationCode != '')
		{
			// get code
			$code = $this->filter('code', 'str');

			if ($registrationCode != $code)
			{
				return $this->error(\XF::phrase('registrationcode_invalid_registration_code_entered'));
			}
		}

		/** @var \XF\Service\User\RegisterForm $regForm */
		$regForm = $this->service('XF:User\RegisterForm', $this->session());

		$input = $this->getRegistrationInput($regForm);
		$registration = $this->setupRegistration($input);

		if (!$registration->validate($errors))
		{
			return $this->error($errors);
		}

		$user = $registration->save();
		$this->finalizeRegistration($user);

		return $this->redirect($this->buildLink('register/complete'));
	}
}