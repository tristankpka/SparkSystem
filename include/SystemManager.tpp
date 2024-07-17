// SystemManager.tpp

template<typename T, typename... Args>
std::shared_ptr<T> SystemManager::registerSystem(Args&&... args) {
    std::shared_ptr<T> system = std::make_shared<T>(std::forward<Args>(args)...);
    systems.push_back(system);
    return system;
}