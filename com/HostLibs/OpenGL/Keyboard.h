#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<map>
class cKeyboard
{
public:
	using KeycallbackFunctionPtr = void(*)(int);
	void SubscribeToKeyEvent(int iKeyNumber, int iKeyEvent, KeycallbackFunctionPtr KeyCallback)
	{
		std::pair<int, int> KeyEventPair(iKeyNumber, iKeyEvent);
		m_multimapSubscribedKeyEvents.insert(std::pair<decltype(KeyEventPair), KeycallbackFunctionPtr>(KeyEventPair, KeyCallback));
	}

	void OnKeyEvent(GLFWwindow* window, int iKeyNumber, int iScancode, int iKeyEvent, int iMods)
	{
		std::pair<int, int> KeyEventPair(iKeyNumber, iKeyEvent);
		std::multimap<std::pair<int, int>, void(*)(int)>::const_iterator Values = m_multimapSubscribedKeyEvents.find(KeyEventPair);
		int iNumResults = m_multimapSubscribedKeyEvents.count(KeyEventPair);
		// Call all functions subscribed to this event
		for (int i = 0; i < iNumResults; i++)
		{
			Values->second(iKeyNumber);
		}
	}

private:
	std::multimap<std::pair<int, int>, KeycallbackFunctionPtr> m_multimapSubscribedKeyEvents; ///< Callback subscribed to a key event. A multimap is used so that there can be more than one subscriber to an event
};