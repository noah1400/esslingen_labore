package swa.filer.repository;

import java.util.List;
import java.util.Optional;

import org.springframework.data.jpa.repository.JpaRepository;

import swa.filer.models.Group;

public interface GroupRepository extends JpaRepository<Group, Long> {
    
    List<Group> findAll();

    Optional<Group> findById(Long id);

}
