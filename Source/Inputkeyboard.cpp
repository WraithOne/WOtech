////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: InputKeyboard.cpp
///
///			Description:
///
///			Created:	01.05.2014
///			Edited:		01.06.2018
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include <pch.h>
#include <Input.h>

namespace WOtech
{
	Platform::Boolean InputManager::KeyboardConnected()
	{
		if (m_keyBoardCapabilities->KeyboardPresent >= 1)
			return true;

		return false;
	}// InputManager KeyboardConnected

	Keyboard_State InputManager::getKeyboardState()
	{
		return m_keyboardState;
	}

	Platform::Boolean InputManager::KeyDown(_In_ Windows::System::VirtualKey Key)
	{
		// TODO: not handcoded
		switch (Key)
		{
		case Windows::System::VirtualKey::None:
			return false;
			break;
		case Windows::System::VirtualKey::LeftButton:
			return false;
			break;
		case Windows::System::VirtualKey::RightButton:
			return false;
			break;
		case Windows::System::VirtualKey::Cancel:
			return false;
			break;
		case Windows::System::VirtualKey::MiddleButton:
			return false;
			break;
		case Windows::System::VirtualKey::XButton1:
			return false;
			break;
		case Windows::System::VirtualKey::XButton2:
			return false;
			break;
		case Windows::System::VirtualKey::Back:
			return m_keyboardState.Back;
			break;
		case Windows::System::VirtualKey::Tab:
			return m_keyboardState.Tab;
			break;
		case Windows::System::VirtualKey::Clear:
			return false;
			break;
		case Windows::System::VirtualKey::Enter:
			return m_keyboardState.Enter;
			break;
		case Windows::System::VirtualKey::Shift:
			return m_keyboardState.LeftShift || m_keyboardState.RightShift;
			break;
		case Windows::System::VirtualKey::Control:
			return m_keyboardState.LeftControl || m_keyboardState.RightControl;
			break;
		case Windows::System::VirtualKey::Menu:
			return m_keyboardState.LeftAlt || m_keyboardState.RightAlt;
			break;
		case Windows::System::VirtualKey::Pause:
			return m_keyboardState.Pause;
			break;
		case Windows::System::VirtualKey::CapitalLock:
			return m_keyboardState.CapsLock;
			break;
		case Windows::System::VirtualKey::Kana:
			return m_keyboardState.Kana;
			break;
			//case Windows::System::VirtualKey::Hangul:
				//return false;
				//break;
		case Windows::System::VirtualKey::Junja:
			return false;
			break;
		case Windows::System::VirtualKey::Final:
			return false;
			break;
			//case Windows::System::VirtualKey::Hanja:
				//return m_keyboardState.;
				//break;
		case Windows::System::VirtualKey::Kanji:
			return m_keyboardState.Kanji;
			break;
		case Windows::System::VirtualKey::Escape:
			return m_keyboardState.Escape;
			break;
		case Windows::System::VirtualKey::Convert:
			return m_keyboardState.ImeConvert;
			break;
		case Windows::System::VirtualKey::NonConvert:
			return m_keyboardState.ImeNoConvert;
			break;
		case Windows::System::VirtualKey::Accept:
			return false;
			break;
		case Windows::System::VirtualKey::ModeChange:
			return false;
			break;
		case Windows::System::VirtualKey::Space:
			return m_keyboardState.Space;
			break;
		case Windows::System::VirtualKey::PageUp:
			return m_keyboardState.PageUp;
			break;
		case Windows::System::VirtualKey::PageDown:
			return m_keyboardState.PageDown;
			break;
		case Windows::System::VirtualKey::End:
			return m_keyboardState.End;
			break;
		case Windows::System::VirtualKey::Home:
			return m_keyboardState.Home;
			break;
		case Windows::System::VirtualKey::Left:
			return m_keyboardState.Left;
			break;
		case Windows::System::VirtualKey::Up:
			return m_keyboardState.Up;
			break;
		case Windows::System::VirtualKey::Right:
			return m_keyboardState.Right;
			break;
		case Windows::System::VirtualKey::Down:
			return m_keyboardState.Down;
			break;
		case Windows::System::VirtualKey::Select:
			return m_keyboardState.Select;
			break;
		case Windows::System::VirtualKey::Print:
			return m_keyboardState.Print;
			break;
		case Windows::System::VirtualKey::Execute:
			return m_keyboardState.Execute;
			break;
		case Windows::System::VirtualKey::Snapshot:
			return m_keyboardState.PrintScreen;
			break;
		case Windows::System::VirtualKey::Insert:
			return m_keyboardState.Insert;
			break;
		case Windows::System::VirtualKey::Delete:
			return m_keyboardState.Delete;
			break;
		case Windows::System::VirtualKey::Help:
			return m_keyboardState.Help;
			break;
		case Windows::System::VirtualKey::Number0:
			return m_keyboardState.D0;
			break;
		case Windows::System::VirtualKey::Number1:
			return m_keyboardState.D1;
			break;
		case Windows::System::VirtualKey::Number2:
			return m_keyboardState.D2;
			break;
		case Windows::System::VirtualKey::Number3:
			return m_keyboardState.D3;
			break;
		case Windows::System::VirtualKey::Number4:
			return m_keyboardState.D4;
			break;
		case Windows::System::VirtualKey::Number5:
			return m_keyboardState.D5;
			break;
		case Windows::System::VirtualKey::Number6:
			return m_keyboardState.D6;
			break;
		case Windows::System::VirtualKey::Number7:
			return m_keyboardState.D7;
			break;
		case Windows::System::VirtualKey::Number8:
			return m_keyboardState.D8;
			break;
		case Windows::System::VirtualKey::Number9:
			return m_keyboardState.D9;
			break;
		case Windows::System::VirtualKey::A:
			return m_keyboardState.A;
			break;
		case Windows::System::VirtualKey::B:
			return m_keyboardState.B;
			break;
		case Windows::System::VirtualKey::C:
			return m_keyboardState.C;
			break;
		case Windows::System::VirtualKey::D:
			return m_keyboardState.D;
			break;
		case Windows::System::VirtualKey::E:
			return m_keyboardState.E;
			break;
		case Windows::System::VirtualKey::F:
			return m_keyboardState.F;
			break;
		case Windows::System::VirtualKey::G:
			return m_keyboardState.G;
			break;
		case Windows::System::VirtualKey::H:
			return m_keyboardState.H;
			break;
		case Windows::System::VirtualKey::I:
			return m_keyboardState.I;
			break;
		case Windows::System::VirtualKey::J:
			return m_keyboardState.J;
			break;
		case Windows::System::VirtualKey::K:
			return m_keyboardState.K;
			break;
		case Windows::System::VirtualKey::L:
			return m_keyboardState.L;
			break;
		case Windows::System::VirtualKey::M:
			return m_keyboardState.M;
			break;
		case Windows::System::VirtualKey::N:
			return m_keyboardState.N;
			break;
		case Windows::System::VirtualKey::O:
			return m_keyboardState.O;
			break;
		case Windows::System::VirtualKey::P:
			return m_keyboardState.P;
			break;
		case Windows::System::VirtualKey::Q:
			return m_keyboardState.Q;
			break;
		case Windows::System::VirtualKey::R:
			return m_keyboardState.R;
			break;
		case Windows::System::VirtualKey::S:
			return m_keyboardState.S;
			break;
		case Windows::System::VirtualKey::T:
			return m_keyboardState.T;
			break;
		case Windows::System::VirtualKey::U:
			return m_keyboardState.U;
			break;
		case Windows::System::VirtualKey::V:
			return m_keyboardState.V;
			break;
		case Windows::System::VirtualKey::W:
			return m_keyboardState.W;
			break;
		case Windows::System::VirtualKey::X:
			return m_keyboardState.X;
			break;
		case Windows::System::VirtualKey::Y:
			return m_keyboardState.Y;
			break;
		case Windows::System::VirtualKey::Z:
			return m_keyboardState.Z;
			break;
		case Windows::System::VirtualKey::LeftWindows:
			return m_keyboardState.LeftWindows;
			break;
		case Windows::System::VirtualKey::RightWindows:
			return m_keyboardState.RightWindows;
			break;
		case Windows::System::VirtualKey::Application:
			return m_keyboardState.Apps;
			break;
		case Windows::System::VirtualKey::Sleep:
			return m_keyboardState.Sleep;
			break;
		case Windows::System::VirtualKey::NumberPad0:
			return m_keyboardState.NumPad0;
			break;
		case Windows::System::VirtualKey::NumberPad1:
			return m_keyboardState.NumPad1;
			break;
		case Windows::System::VirtualKey::NumberPad2:
			return m_keyboardState.NumPad2;
			break;
		case Windows::System::VirtualKey::NumberPad3:
			return m_keyboardState.NumPad3;
			break;
		case Windows::System::VirtualKey::NumberPad4:
			return m_keyboardState.NumPad4;
			break;
		case Windows::System::VirtualKey::NumberPad5:
			return m_keyboardState.NumPad5;
			break;
		case Windows::System::VirtualKey::NumberPad6:
			return m_keyboardState.NumPad6;
			break;
		case Windows::System::VirtualKey::NumberPad7:
			return m_keyboardState.NumPad7;
			break;
		case Windows::System::VirtualKey::NumberPad8:
			return m_keyboardState.NumPad8;
			break;
		case Windows::System::VirtualKey::NumberPad9:
			return m_keyboardState.NumPad9;
			break;
		case Windows::System::VirtualKey::Multiply:
			return m_keyboardState.Multiply;
			break;
		case Windows::System::VirtualKey::Add:
			return m_keyboardState.Add;
			break;
		case Windows::System::VirtualKey::Separator:
			return m_keyboardState.Separator;
			break;
		case Windows::System::VirtualKey::Subtract:
			return m_keyboardState.Subtract;
			break;
		case Windows::System::VirtualKey::Decimal:
			return m_keyboardState.Decimal;
			break;
		case Windows::System::VirtualKey::Divide:
			return m_keyboardState.Divide;
			break;
		case Windows::System::VirtualKey::F1:
			return m_keyboardState.F1;
			break;
		case Windows::System::VirtualKey::F2:
			return m_keyboardState.F2;
			break;
		case Windows::System::VirtualKey::F3:
			return m_keyboardState.F3;
			break;
		case Windows::System::VirtualKey::F4:
			return m_keyboardState.F4;
			break;
		case Windows::System::VirtualKey::F5:
			return m_keyboardState.F5;
			break;
		case Windows::System::VirtualKey::F6:
			return m_keyboardState.F6;
			break;
		case Windows::System::VirtualKey::F7:
			return m_keyboardState.F7;
			break;
		case Windows::System::VirtualKey::F8:
			return m_keyboardState.F8;
			break;
		case Windows::System::VirtualKey::F9:
			return m_keyboardState.F9;
			break;
		case Windows::System::VirtualKey::F10:
			return m_keyboardState.F10;
			break;
		case Windows::System::VirtualKey::F11:
			return m_keyboardState.F11;
			break;
		case Windows::System::VirtualKey::F12:
			return m_keyboardState.F12;
			break;
		case Windows::System::VirtualKey::F13:
			return m_keyboardState.F13;
			break;
		case Windows::System::VirtualKey::F14:
			return m_keyboardState.F14;
			break;
		case Windows::System::VirtualKey::F15:
			return m_keyboardState.F15;
			break;
		case Windows::System::VirtualKey::F16:
			return m_keyboardState.F16;
			break;
		case Windows::System::VirtualKey::F17:
			return m_keyboardState.F17;
			break;
		case Windows::System::VirtualKey::F18:
			return m_keyboardState.F18;
			break;
		case Windows::System::VirtualKey::F19:
			return m_keyboardState.F19;
			break;
		case Windows::System::VirtualKey::F20:
			return m_keyboardState.F20;
			break;
		case Windows::System::VirtualKey::F21:
			return m_keyboardState.F21;
			break;
		case Windows::System::VirtualKey::F22:
			return m_keyboardState.F22;
			break;
		case Windows::System::VirtualKey::F23:
			return m_keyboardState.F23;
			break;
		case Windows::System::VirtualKey::F24:
			return m_keyboardState.F24;
			break;
		case Windows::System::VirtualKey::NavigationView:
			return false;
			break;
		case Windows::System::VirtualKey::NavigationMenu:
			return false;
			break;
		case Windows::System::VirtualKey::NavigationUp:
			return false;
			break;
		case Windows::System::VirtualKey::NavigationDown:
			return false;
			break;
		case Windows::System::VirtualKey::NavigationLeft:
			return false;
			break;
		case Windows::System::VirtualKey::NavigationRight:
			return false;
			break;
		case Windows::System::VirtualKey::NavigationAccept:
			return false;
			break;
		case Windows::System::VirtualKey::NavigationCancel:
			return false;
			break;
		case Windows::System::VirtualKey::NumberKeyLock:
			return m_keyboardState.NumLock;
			break;
		case Windows::System::VirtualKey::Scroll:
			return m_keyboardState.Scroll;
			break;
		case Windows::System::VirtualKey::LeftShift:
			return m_keyboardState.LeftShift;
			break;
		case Windows::System::VirtualKey::RightShift:
			return m_keyboardState.RightShift;
			break;
		case Windows::System::VirtualKey::LeftControl:
			return m_keyboardState.LeftControl;
			break;
		case Windows::System::VirtualKey::RightControl:
			return m_keyboardState.RightControl;
			break;
		case Windows::System::VirtualKey::LeftMenu:
			return m_keyboardState.LeftAlt;
			break;
		case Windows::System::VirtualKey::RightMenu:
			return m_keyboardState.RightAlt;
			break;
		case Windows::System::VirtualKey::GoBack:
			return m_keyboardState.BrowserBack;
			break;
		case Windows::System::VirtualKey::GoForward:
			return m_keyboardState.BrowserForward;
			break;
		case Windows::System::VirtualKey::Refresh:
			return m_keyboardState.BrowserRefresh;
			break;
		case Windows::System::VirtualKey::Stop:
			return m_keyboardState.BrowserStop;
			break;
		case Windows::System::VirtualKey::Search:
			return m_keyboardState.BrowserSearch;
			break;
		case Windows::System::VirtualKey::Favorites:
			return m_keyboardState.BrowserFavorites;
			break;
		case Windows::System::VirtualKey::GoHome:
			return m_keyboardState.BrowserHome;
			break;
		case Windows::System::VirtualKey::GamepadA:
			return false;
			break;
		case Windows::System::VirtualKey::GamepadB:
			return false;
			break;
		case Windows::System::VirtualKey::GamepadX:
			return false;
			break;
		case Windows::System::VirtualKey::GamepadY:
			return false;
			break;
		case Windows::System::VirtualKey::GamepadRightShoulder:
			return false;
			break;
		case Windows::System::VirtualKey::GamepadLeftShoulder:
			return false;
			break;
		case Windows::System::VirtualKey::GamepadLeftTrigger:
			return false;
			break;
		case Windows::System::VirtualKey::GamepadRightTrigger:
			return false;
			break;
		case Windows::System::VirtualKey::GamepadDPadUp:
			return false;
			break;
		case Windows::System::VirtualKey::GamepadDPadDown:
			return false;
			break;
		case Windows::System::VirtualKey::GamepadDPadLeft:
			return false;
			break;
		case Windows::System::VirtualKey::GamepadDPadRight:
			return false;
			break;
		case Windows::System::VirtualKey::GamepadMenu:
			return false;
			break;
		case Windows::System::VirtualKey::GamepadView:
			return false;
			break;
		case Windows::System::VirtualKey::GamepadLeftThumbstickButton:
			return false;
			break;
		case Windows::System::VirtualKey::GamepadRightThumbstickButton:
			return false;
			break;
		case Windows::System::VirtualKey::GamepadLeftThumbstickUp:
			return false;
			break;
		case Windows::System::VirtualKey::GamepadLeftThumbstickDown:
			return false;
			break;
		case Windows::System::VirtualKey::GamepadLeftThumbstickRight:
			return false;
			break;
		case Windows::System::VirtualKey::GamepadLeftThumbstickLeft:
			return false;
			break;
		case Windows::System::VirtualKey::GamepadRightThumbstickUp:
			return false;
			break;
		case Windows::System::VirtualKey::GamepadRightThumbstickDown:
			return false;
			break;
		case Windows::System::VirtualKey::GamepadRightThumbstickRight:
			return false;
			break;
		case Windows::System::VirtualKey::GamepadRightThumbstickLeft:
			return false;
			break;
		default:
			return false;
			break;
		}
	}// InputManager KeyboardKeyDown
}//namespace WOtech