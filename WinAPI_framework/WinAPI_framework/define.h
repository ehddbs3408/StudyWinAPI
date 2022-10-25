#pragma once
#define SINGLE(type) static type* GetInst() { static type mrg; return &mrg;}
#define WINDOW_NAME L"Game framework"