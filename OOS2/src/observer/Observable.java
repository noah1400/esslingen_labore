package observer;

public interface Observable<T> {
    void addObserver(Observer<T> o);
    void deleteObserver(Observer<T> o);
    void notifyObservers();
    void notifyObservers(T arg);
    void deleteObservers();
    void setChanged();
    void clearChanged();
    boolean hasChanged();
    int countObservers();
}
