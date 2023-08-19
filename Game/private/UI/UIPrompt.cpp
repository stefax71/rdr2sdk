#include "../../public/UI/UIPrompt.h"
#include "../../public/native/natives.h"
#include "../../public/RDREnums.h"

UIPrompt::UIPrompt(const char* text, hud::EInputType control)
	: UIPrompt(text, control, Standard)
{
}

UIPrompt::UIPrompt(const char* text, hud::EInputType control, PromptMode mode)
{
	handle = HUD::_UI_PROMPT_REGISTER_BEGIN(); // _UIPROMPT_REGISTER_BEGIN
	setControl(control);
	setText(text);
	setTargetEntity(NULL);
	setMode(mode);
	HUD::_UI_PROMPT_REGISTER_END(this->handle); // _UIPROMPT_REGISTER_END

	semiHoldShouldReturn = false;
	disable();
	hide();
}

Entity UIPrompt::getTargetEntity()
{
	return this->targetEntity;
}

bool UIPrompt::getIsEnabled()
{
	return isEnabled;
}

bool UIPrompt::getIsVisible()
{
	return isVisible;
}

void UIPrompt::setText(const char* text)
{
	this->text = text;
	const char* textLabel = MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", text);
	HUD::_0x5DD02A8318420DD7(this->handle, (Any*)textLabel); // _UIPROMPT_SET_TEXT
}

void UIPrompt::setControl(hud::EInputType control)
{
	this->control = control;
	HUD::_UI_PROMPT_SET_CONTROL_ACTION(this->handle, static_cast<unsigned int>(control)); // _UIPROMPT_SET_CONTROL_ACTION
}

void UIPrompt::setTargetEntity(Entity target)
{
	this->targetEntity = target;

	if (!target)
	{

		HUD::_UI_PROMPT_REMOVE_GROUP(this->handle, 0);
		return;
	}

	int targetEntityGroupId = HUD::_UI_PROMPT_GET_GROUP_ID_FOR_TARGET_ENTITY(target); // _UIPROMPT_GET_GROUP_ID_FOR_TARGET_ENTITY 
	if (targetEntityGroupId)
	{
		HUD::_UI_PROMPT_SET_GROUP(this->handle, targetEntityGroupId, 0); // _UIPROMPT_SET_GROUP
	}
}

void UIPrompt::setPriority(int priority) 
{
	HUD::_UI_PROMPT_SET_PRIORITY(handle, priority); // _UIPROMPT_SET_PRIORITY
}

void UIPrompt::setMode(PromptMode mode)
{
	this->mode = mode;

	switch (mode)
	{
	case Standard:
		HUD::_UI_PROMPT_SET_STANDARD_MODE(handle, 1); // UIPROMOT_SET_STANDARD_MODE
		break;

	case Hold:
		HUD::_UI_PROMPT_SET_HOLD_MODE(handle, 1); // _UIPROMPT_SET_HOLD_MODE
		break;
	case SemiHold:
		HUD::_UI_PROMPT_SET_HOLD_MODE(handle, 1); // _UIPROMPT_SET_HOLD_MODE
		break;
	}
}

bool UIPrompt::isActivatedByPlayer()
{
	if (!this->isEnabled)
	{
		return false;
	}

	switch (mode)
	{
	case Standard:
		return HUD::_UI_PROMPT_HAS_STANDARD_MODE_COMPLETED(handle, 0); // _UIPROMPT_HAS_STANDARD_MODE_COMPLETED
	case Hold:
		return HUD::_UI_PROMPT_HAS_HOLD_MODE_COMPLETED(handle); // _UIPROMPT_HAS_HOLD_MODE_COMPLETED
	case SemiHold:
		if (HUD::_UI_PROMPT_HAS_HOLD_MODE_COMPLETED(handle))
		{
			if (semiHoldShouldReturn == true)
			{
				return false;
			}

			semiHoldShouldReturn = true;
			return true;
		}
		else
		{
			semiHoldShouldReturn = false;
		}
	}
}


void UIPrompt::remove()
{
	HUD::_UI_PROMPT_DELETE(handle);
}

void UIPrompt::show()
{
	isVisible = true;
	update();
}

void UIPrompt::hide()
{
	isVisible = false;
	update();
}

void UIPrompt::disable()
{
	isEnabled = false;
	update();
}

void UIPrompt::enable()
{
	isEnabled = true;
	update();
}


void UIPrompt::update()
{
	HUD::_UI_PROMPT_SET_ENABLED(this->handle, isEnabled); // _UIPROMPT_SET_ENABLED
	HUD::_UI_PROMPT_SET_VISIBLE(this->handle, isVisible); // _UIPROMPT_SET_VISIBLE
}
