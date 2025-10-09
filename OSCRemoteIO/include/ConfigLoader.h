#include <Preferences.h>

Preferences prefs;

template <typename T>
class ConfigLoader
{
private:
    const char* m_namespace;
private:

    T* m_loadedValue;

public:
    const T* getLoadedConfig()
    {
        prefs.begin(m_namespace);
        
    }
public:
    ConfigLoader(const char* namespace):
        m_namespace(namespace)
    {

    }
};
