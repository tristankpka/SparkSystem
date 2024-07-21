// SystemManager.tpp

template<typename T, typename... Args>
std::shared_ptr<T> SystemManager::registerSystem(Args&&... args) {
    auto system = std::make_shared<T>(std::forward<Args>(args)...);
    systems[typeid(T)] = system;
    return system;
}