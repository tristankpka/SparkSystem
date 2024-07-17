//
// Created by Klemp on 11-Jul-24.
//

template<ValidComponent T>
typename Component<T>::Id Component<T>::nextId = 0;

template<ValidComponent T>
typename Component<T>::Id Component<T>::getId() {
    static const Id id = nextId++;
    return id;
}