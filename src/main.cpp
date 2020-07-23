#include <stdint.h>

#include "boards.h"
#include "bsp.h"
#include "app_timer.h"
#include "app_error.h"
#include "nrfx_nfct.h"

#include "nfc_tag_emulation/nxp_ntag21x_emulator.h"
#include "app/app_logs.h"
#include "app/app_clock.h"
#include "usb/usb.h"
#include "usb/usb_msc.h"
#include "display/display_screen.h"

#include "global/global_data.h"

using NtagPayload = nfc_tag_emulation::nxp_ntag21x::Ntag21XPayload;

nfc_tag_emulation::nxp_ntag21x::Ntag21xEmulator ntag215Emulator;

// a payload to test with
extern const uint8_t t2tTesterBin[540];
NtagPayload tester(t2tTesterBin, 540);
NtagPayload* targetPayload = &tester;

// event handler for board support events (a la button)
void bsp_evt_handler(bsp_event_t evt)
{
    switch (evt)
    {
        case BSP_EVENT_KEY_0:
			I("Button pressed. No handler yet.");
			break;
        default:
			D("[BSP] Unhandled event: %d", evt);
            break;
    }
}

// configure bsp
void bsp_configuration()
{
    uint32_t err_code;

	const uint32_t bspFlags = BSP_INIT_LEDS | BSP_INIT_BUTTONS;

    err_code = bsp_init(bspFlags, bsp_evt_handler);
    APP_ERROR_CHECK(err_code);
}

int main(int argc, char** argv)
{
    app_log_init();

	D("=====================================");
	I("Application starting.");

	app_clocks_initialize();

    ret_code_t err_code = app_timer_init();
    APP_ERROR_CHECK(err_code);

	bsp_configuration();

	// setup USB
	Usb::Device::Initialize();
	Usb::MassStorageClass msc;
	Usb::Device::Enable();

	// setup SDC
	SDCARD.Mount();
	Usb::Device::RegisterListener(&SDCARD);

	// setup LCD
	Display::Screen screen;
	screen.ClearBackground();
	screen.DrawText("Hello frans!", 5, 5);
	screen.DrawText("This is where the fun begins!", 5, 100, MAGENTA, true, false);
	screen.DrawText("`'~,._.,~'`", 5, 45, ORANGE, true, true);
	screen.DrawText("Coming soon: a completely boring\nUI! Also, I can word wrap!", 5, 200, CYAN, true, false);
	screen.DrawText("It's not the fastest,\nnor the prettiest.", 5, 240, GREENYELLOW, true, false);
	screen.DrawText("But dammit, it works.", 5, 300, PINK, true, false);

    // Setup NFC Tag
	ntag215Emulator.Initialize();

	// Set the initial payload
	ntag215Emulator.SetPayload(targetPayload);

	// And turn the tag on!
	ntag215Emulator.EnableTag();

	D("Application waiting for events!");
    while (1)
    {
        app_log_flush();

		Usb::Device::Update();

		// why wfe/sev/wfe? event clearing and sleep for power optimization.
		// see: https://devzone.nordicsemi.com/f/nordic-q-a/10424/nrf51422-won-t-sleep
        __WFE();
        __SEV();
        __WFE();
    }
}
