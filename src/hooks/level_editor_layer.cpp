#include "level_editor_layer.hpp"

#include <Geode/utils/web.hpp>

#include "gjbasegamelayer.hpp"
#include "triggers/gjeffectmanager.hpp"
#include "ui/game/userlist/userlist.hpp"
#include <managers/settings.hpp>
#include <managers/hook.hpp>
#include <managers/popup.hpp>

using namespace geode::prelude;

/* Hooks */

bool GlobedLevelEditorLayer::init(GJGameLevel* level, bool p1) {
    GlobedLevelEditorLayer::fromEditor = true;

    auto gjbgl = static_cast<GlobedGJBGL*>(static_cast<GJBaseGameLayer*>(this));

    gjbgl->setupPreInit(level, true);

    if (!LevelEditorLayer::init(level, p1)) return false;

    gjbgl->setupAll();

    gjbgl->m_fields->setupWasCompleted = true;

    auto& settings = GlobedSettings::get();

#if GLOBED_GP_CHANGES
    if (settings.globed.editorChanges) {
        HookManager::get().enableGroup(HookManager::Group::EditorTriggerPopups);

        if (!settings.flags.seenGlobalTriggerGuide) {
            settings.flags.seenGlobalTriggerGuide = true;
            auto alert = geode::createQuickPopup("Globed", fmt::format("Visit the global trigger guide page? <cy>({})</c>\n\n<cg>Highly recommended</c>, if you've never worked with them before.", globed::string<"global-trigger-page">()), "No", "Yes", [](auto, bool agree) {
                if (!agree) return;

                geode::utils::web::openLinkInBrowser(globed::string<"global-trigger-page">());
            }, false);

            // TODO: convert to .quickAlert icbb
            auto pref = PopupManager::get().manage(alert);
            pref.showQueue();
        }
    } else {
        HookManager::get().disableGroup(HookManager::Group::EditorTriggerPopups);
    }

    globed::toggleEditorTriggerHooks(settings.globed.editorChanges);
#endif

    if (!gjbgl || !gjbgl->established()) return true;

    EditorUI *eui = EditorUI::get();
    if (eui) {
        CCNode *settingsMenu = eui->getChildByIDRecursive("settings-menu");
        if (settingsMenu) {
            Build<CCSprite>::createSpriteName("icon-players.png"_spr)
                .scale(0.9f)
                .intoMenuItem([](auto) {
                    GlobedUserListPopup::create()->show();
                })
                .id("btn-open-playerlist"_spr)
                .parent(settingsMenu);

            settingsMenu->updateLayout();
        }
    }

    return true;
}
