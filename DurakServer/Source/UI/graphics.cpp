#include <UI/graphics.hpp>
#include <UI/window.hpp>

#include <d2d1.h>
#include <wincodec.h>
#include <dwrite.h>

namespace UI
{
    static constexpr float width = Window::width;
    static constexpr float height = Window::height;

    using Durak::GameState;
    static GameState gameState;

    static bool isRenderingNeeded;

    static HRESULT hResult;
    static struct 
    {
        ID2D1Factory* pFactory;
        ID2D1HwndRenderTarget* pRenderTarget;
        IDWriteFactory* pDWriteFactory;
        ID2D1SolidColorBrush* pBrush;

        IDWriteTextFormat* pTextFormatWaitingForPlayers;
        IDWriteTextLayout* pTextLayoutWaitingForPlayers;
    } d2d1;

    template<class T>
    static void safe_release(T** ppT)
    {
        if (*ppT != nullptr)
        {
            (*ppT)->Release();
            (*ppT) = nullptr;
        }
    }

    static void create_text_layout(std::wstring&& text, IDWriteTextLayout** ppLayout);
    static void draw_text(float x, float y, IDWriteTextLayout* ppLayout);

    /////////////////////////////////
    
    void Graphics::initialize()
    {
        /*
         * Create D2D1 Factory
         */
        {
            auto factoryType = D2D1_FACTORY_TYPE_SINGLE_THREADED;
            hResult = D2D1CreateFactory(factoryType, &d2d1.pFactory);
            if (FAILED(hResult))
            {
                throw new std::runtime_error("D2D1CreateFactory has failed!");
            }
        }

        /*
         * Create D2D1 Render Target
         */
        {
            auto renderTargetProperties = D2D1::RenderTargetProperties();
            auto pixelSize = D2D1::SizeU(width, height);
            auto hwndRenderTargetProperties = D2D1::HwndRenderTargetProperties(Window::get_hWnd(), pixelSize);
            hResult = d2d1.pFactory->CreateHwndRenderTarget(renderTargetProperties, hwndRenderTargetProperties, &d2d1.pRenderTarget);
            if (FAILED(hResult))
            {
                throw new std::runtime_error("CreateHwndRenderTarget has failed!");
            }
        }

        /*
         * Create DWrite Factory
         */
        {
            auto factoryType = DWRITE_FACTORY_TYPE_SHARED;
            auto iid = __uuidof(IDWriteFactory);
            auto factory = reinterpret_cast<IUnknown**>(&d2d1.pDWriteFactory);
            hResult = DWriteCreateFactory(factoryType, iid, factory);
            if (FAILED(hResult))
            {
                throw new std::runtime_error("DWriteCreateFactory has failed!");
            }
        }

        /*
         * Create default text format
         */
        {
            // Waiting for players
            {
                auto family = L"Comic Sans MS";
                auto weight = DWRITE_FONT_WEIGHT_BOLD;
                auto style = DWRITE_FONT_STYLE_NORMAL;
                auto stretch = DWRITE_FONT_STRETCH_NORMAL;
                auto size = 36.0f;
                hResult = d2d1.pDWriteFactory->CreateTextFormat(family, NULL, weight, style, stretch, size, L"", &d2d1.pTextFormatWaitingForPlayers);
                if (FAILED(hResult))
                {
                    throw new std::runtime_error("CreateTextFormat has failed!");
                }
            }
        }

        /*
         * Create brush
         */
        {
            auto color = D2D1::ColorF(0, 0); // Black transparent
            hResult = d2d1.pRenderTarget->CreateSolidColorBrush(color, &d2d1.pBrush);
            if (FAILED(hResult))
            {
                throw new std::runtime_error("CreateSolidColorBrush has failed!");
            }
        }
    }

    void Graphics::render()
    {
        if (!isRenderingNeeded)
        {
            return;
        }

        d2d1.pRenderTarget->BeginDraw();
        d2d1.pRenderTarget->Clear(D2D1::ColorF(1, 1, 1)); // White background
        switch (gameState)
        {
            case GameState::WaitingForPlayers:
            {
                DWRITE_TEXT_METRICS metrics{};
                d2d1.pTextLayoutWaitingForPlayers->GetMetrics(&metrics);

                // Center at: 50% width, 25% height
                float x = (width - metrics.width) * 0.5;
                float y = (height - metrics.height) * 0.25;

                // Text color: dark gray opaque
                d2d1.pBrush->SetColor(D2D1::ColorF(D2D1::ColorF::DarkGray));
                draw_text(x, y, d2d1.pTextLayoutWaitingForPlayers);

                // Continous rendering isn't needed
                isRenderingNeeded = false;
            } break;
        }
        d2d1.pRenderTarget->EndDraw();
    }

    void Graphics::cleanup()
    {
        safe_release(&d2d1.pFactory);
        safe_release(&d2d1.pRenderTarget);
        safe_release(&d2d1.pDWriteFactory);
        safe_release(&d2d1.pBrush);
        safe_release(&d2d1.pFactory);
        safe_release(&d2d1.pTextFormatWaitingForPlayers);
        safe_release(&d2d1.pTextLayoutWaitingForPlayers);
    }

    void Graphics::set_state(GameState state)
    {
        switch (state)
        {
        case GameState::WaitingForPlayers:
            create_text_layout(L"Waiting for players", &d2d1.pTextLayoutWaitingForPlayers);
            gameState = GameState::WaitingForPlayers;
            break;
        }

        isRenderingNeeded = true;
    }

    /////////////////////////////////

    void create_text_layout(std::wstring&& text, IDWriteTextLayout** ppLayout)
    {
        auto cstr = text.c_str();
        auto len = text.length();
        auto format = d2d1.pTextFormatWaitingForPlayers;
        hResult = d2d1.pDWriteFactory->CreateTextLayout(cstr, len, format, width, height, ppLayout);
    }

    void draw_text(float x, float y, IDWriteTextLayout* pLayout)
    {
        d2d1.pRenderTarget->DrawTextLayout(D2D1::Point2F(x, y), pLayout, d2d1.pBrush);
    }
} // namespace UI
