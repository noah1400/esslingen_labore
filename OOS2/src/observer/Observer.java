package observer;

public interface Observer<T> {
    void update(Observable<T> observable, T newValue);
}