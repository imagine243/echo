#pragma once

#include "build_settings.h"

namespace Echo
{
    class MacBuildSettings : public BuildSettings
    {
        ECHO_SINGLETON_CLASS(MacBuildSettings, BuildSettings)
        
    public:
        MacBuildSettings();
        virtual ~MacBuildSettings();
        
        // instance
        static MacBuildSettings* instance();
        
        // build
        virtual void build() override;

		// get name
		virtual const char* getPlatformName() const override { return "Mac"; }

		// platform thumbnail
		virtual ImagePtr getPlatformThumbnail() const override;
        
        // icon res path
        void setIconRes(const ResourcePath& path);
        const ResourcePath& getIconRes() { return m_iconRes; }
        
        // set output directory
        virtual void setOutputDir(const String& outputDir) override;
        
        // get final result path
        virtual String getFinalResultPath() override;
        
    private:
        // output directory
        bool prepare();
        
        // copy
        void copySrc();
        void copyRes();
        
        // write config
        void writeModuleConfig();
        
    private:
        ResourcePath            m_iconRes;
        String                  m_rootDir;
        String                  m_projectDir;
        String                  m_outputDir;
        String                  m_solutionDir;
    };
}
