package swa.filer.repository;


import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.query.Param;
import swa.filer.models.File;

import java.util.List;


public interface FileRepository extends JpaRepository<File, Long> {

    @Query("SELECT f FROM File f WHERE f.directory_id.directory_id = :dirId")
    List<File> findFilesByDirID(@Param("dirId") String dirId);

    @Query("SELECT f FROM File f " +
            "JOIN Directory d ON f.directory_id = d.id " +
            "JOIN User u ON d.user_id = u.id " +
            "WHERE u.id = :userId AND d.id = :dirId")
    File findFileByUserIDAndDirID(@Param("userId") Long userId,
                                  @Param("dirId") Long dirId);


    @Query("SELECT f FROM File f WHERE f.id = :fileId")
    File findFileById(@Param("fileId") Long fileId);
}