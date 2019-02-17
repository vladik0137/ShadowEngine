#pragma once
//#include "ShadowWin.h"
#include <Windows.h>

#include "ShadowException.h"
#include "Keyboard.h"
#include "Mouse.h"

#include <optional>

class ShadowWindow
{
public:
	class Exception : public ShadowException
	{
	public:
		Exception(int line, const char* file, HRESULT hr) noexcept;
		const char* what() const noexcept override;
		virtual const char* GetType() const noexcept;
		static std::string TranslateErrorCode(HRESULT hr) noexcept;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorString() const noexcept;
	private:
		HRESULT hr;
	};
private:
	// manage registration/cleanup of window class
	class WindowClass
	{
	public:
		static const char* GetName() noexcept;
		static HINSTANCE GetInstance() noexcept;
	private:
		WindowClass() noexcept;
		~WindowClass();
		WindowClass(const WindowClass&) = delete;
		WindowClass& operator=(const WindowClass&) = delete;
		static constexpr const char* wndClassName = "Shadow Engine Window";
		static WindowClass wndClass;
		HINSTANCE hInst;
	};

public:
	ShadowWindow(int width, int height, const char* name) noexcept;
	~ShadowWindow();
	ShadowWindow(const ShadowWindow&) = delete;
	ShadowWindow& operator=(const ShadowWindow&) = delete;
	void SetTitle(const std::string& title);
	static std::optional<int> ProcessMessages();
private:
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
public:
	Keyboard kbd;
	Mouse mouse;
private:
	int width;
	int height;
	HWND hWnd;
};

#define SHWND_EXCEPT(hr) ShadowWindow::Exception(__LINE__,__FILE__, hr)
#define SHWND_LAST_EXCEPT(hr) ShadowWindow::Exception(__LINE__,__FILE__, GetLastError())