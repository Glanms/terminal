// Copyright (c) Microsoft Corporation.
// Licensed under the MIT license.

#pragma once

#include "CommandPalette.g.h"
#include "../../cascadia/inc/cppwinrt_utils.h"

namespace winrt::TerminalApp::implementation
{
    struct CommandPalette : CommandPaletteT<CommandPalette>
    {
        CommandPalette();

        Windows::Foundation::Collections::IObservableVector<TerminalApp::Command> FilteredActions();
        void SetActions(Windows::Foundation::Collections::IVector<TerminalApp::Command> const& actions);
        void ToggleVisibility();
        void SetDispatch(const winrt::TerminalApp::ShortcutActionDispatch& dispatch);
        void SetKeyBindings(const winrt::Microsoft::Terminal::Settings::IKeyBindings& bindings);

        // TabSwitcherMode Specific
        void ToggleTabSwitcher(const TerminalApp::AnchorKey& anchorKey);
        void OnTabsChanged(const Windows::Foundation::IInspectable& s, const Windows::Foundation::Collections::IVectorChangedEventArgs& e);

        TYPED_EVENT(Closed, TerminalApp::CommandPalette, winrt::Windows::UI::Xaml::RoutedEventArgs);

    private:
        friend struct CommandPaletteT<CommandPalette>; // for Xaml to bind events

        Windows::Foundation::Collections::IObservableVector<TerminalApp::Command> _filteredActions{ nullptr };
        Windows::Foundation::Collections::IVector<TerminalApp::Command> _allActions{ nullptr };
        winrt::TerminalApp::ShortcutActionDispatch _dispatch;
        winrt::Microsoft::Terminal::Settings::IKeyBindings _keyBindings;

        void _filterTextChanged(Windows::Foundation::IInspectable const& sender,
                                Windows::UI::Xaml::RoutedEventArgs const& args);
        void _previewKeyDownHandler(Windows::Foundation::IInspectable const& sender,
                                    Windows::UI::Xaml::Input::KeyRoutedEventArgs const& e);
        void _keyDownHandler(Windows::Foundation::IInspectable const& sender,
                             Windows::UI::Xaml::Input::KeyRoutedEventArgs const& e);
        void _keyUpHandler(Windows::Foundation::IInspectable const& sender,
                             Windows::UI::Xaml::Input::KeyRoutedEventArgs const& e);

        void _rootPointerPressed(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e);
        void _backdropPointerPressed(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e);

        void _listItemClicked(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::Controls::ItemClickEventArgs const& e);

        void _selectNextItem(const bool moveDown);

        void _updateFilteredActions();
        static int _getWeight(const winrt::hstring& searchText, const winrt::hstring& name);
        void _close();

        // TabSwitcherMode Specific
        TerminalApp::AnchorKey _anchorKey;
        bool _tabSwitcherMode{ true };
        void GenerateCommandForTab(const uint32_t idx, bool inserted, winrt::TerminalApp::Tab& tab);
        void RefreshTabIndices(const uint32_t startIdx);
        Windows::Foundation::Collections::IVector<TerminalApp::Command> _allTabActions{ nullptr };
    };
}

namespace winrt::TerminalApp::factory_implementation
{
    BASIC_FACTORY(CommandPalette);
}
