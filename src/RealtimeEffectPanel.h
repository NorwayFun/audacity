/*!********************************************************************

   Audacity: A Digital Audio Editor

   @file RealtimeEffectPanel.cpp

   @author Vitaly Sverchinsky
   
**********************************************************************/

#pragma once

#include <memory>
#include <wx/scrolwin.h>
#include <wx/weakref.h>

#include "ThemedWrappers.h"
#include "Observer.h"

class Track;

class wxButton;
class wxStaticText;
class wxBitmapButton;

class RealtimeEffectListWindow;
class AudacityProject;

/**
 * \brief UI Panel that displays realtime effects from the effect stack of
 * an individual track, provides controls for accessing effect settings,
 * stack manipulation (reorder, add, remove)
 */
class RealtimeEffectPanel : public wxWindow
{
   ThemedButtonWrapper<wxBitmapButton>* mToggleEffects{nullptr};
   wxStaticText* mTrackTitle {nullptr};
   RealtimeEffectListWindow* mEffectList{nullptr};
   AudacityProject& mProject;

   std::weak_ptr<Track> mCurrentTrack;

   Observer::Subscription mTrackListChanged;
   Observer::Subscription mUndoSubscription;

   std::vector<std::shared_ptr<Track>> mPotentiallyRemovedTracks;

   // RealtimeEffectPanel is wrapped using ThemedWindowWrapper,
   // so we cannot subscribe to Prefs directly
   struct PrefsListenerHelper;
   std::unique_ptr<PrefsListenerHelper> mPrefsListenerHelper;

public:
   RealtimeEffectPanel(
      AudacityProject& project, wxWindow* parent,
                wxWindowID id,
                const wxPoint& pos = wxDefaultPosition,
                const wxSize& size = wxDefaultSize,
                long style = 0,
                const wxString& name = wxPanelNameStr);

   ~RealtimeEffectPanel() override;

   /**
    * \brief Shows effects from the effect stack of the track
    * \param track Pointer to the existing track, or null
    */
   void SetTrack(const std::shared_ptr<Track>& track);
   void ResetTrack();
};
