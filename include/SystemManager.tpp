// SystemManager.tpp
#ifndef SYSTEMMANAGER_TPP
#define SYSTEMMANAGER_TPP

template<typename T, typename... Args>
std::shared_ptr<T> SystemManager::registerSystem(Args&&... args) {
    auto system = std::make_shared<T>(std::forward<Args>(args)...);
    m_systems[typeid(T)] = system;
    return system;
}
#endif // SYSTEMMANAGER_TPP
