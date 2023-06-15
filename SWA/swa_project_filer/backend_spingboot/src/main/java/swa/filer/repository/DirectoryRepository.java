package swa.filer.repository;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.query.Param;
import swa.filer.models.Directory;

import java.util.List;
import java.util.Optional;

public interface DirectoryRepository extends JpaRepository<Directory, Long> {

     Optional<Directory> findById(Long directory_id);

     @Query("SELECT d FROM Directory d WHERE d.user_id.id = :userId")
     List<Directory> findAllByUserId(@Param("userId") Long userId);

     @Query("SELECT d FROM Directory d WHERE d.user_id.id = :userId AND d.name = :dir_name")
     List <Directory> findDirIDByName(@Param("userId") Long userId,
                                                 @Param("dir_name") String dir_name);
     @Query("SELECT d FROM Directory d WHERE d.user_id.id = :userId AND d.subdir_id.name = :dir_name")
     List <Directory> findSubDirByDirIDAndUserID(@Param("userId") Long userId,
                                                 @Param("dir_name") String dir_name);
     @Query("SELECT d FROM Directory d WHERE d.user_id.id = :userId AND d.subdir_id.directory_id IS NULL")
     List <Directory> findHomeDirByDirByUserID(@Param("userId") Long userId);
}