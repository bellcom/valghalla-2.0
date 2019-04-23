angular.module('volunteersTable', ['angular-table']).controller('volunteerController', ['$scope', '$window', '$filter', function ($scope, $window, $filter) {
  $scope.originalList = [];
  $scope.filteredList = $scope.originalList;

  jQuery(document).on('volunteersLoaded', function () {
    $scope.originalList = $window.valghalla_volunteers;
    $scope.filteredList = $scope.originalList.filter($scope.validateVolunteer);

    $scope.$apply();
    // $scope.$evalAsync();
  });

  $scope.updateFilteredList = function () {
    $scope.filteredList = $scope.originalList.filter($scope.validateVolunteer);

    $scope.filteredList = $filter('filter')($scope.filteredList, $scope.query);
  };

  $scope.config = {
    itemsPerPage: 10,
    maxPages: 5,
    fillLastPage: "yes"
  };

  $scope.validateVolunteer = function(value) {
    if (volunteer_info.validate_citizenship && !value.citizenship) {
      return false;
    }
    if (volunteer_info.validate_municipality && !value.municipality) {
      return false;
    }

    if (volunteer_info.validate_civil_status && !value.civil_status) {
      return false;
    }

    return true;
  }


}]);
