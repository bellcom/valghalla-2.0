angular.module('volunteersTable', ['angular-table']).controller('volunteerController', ['$scope', '$window', '$filter', function ($scope, $window, $filter) {
  $scope.originalList = [];
  $scope.filteredList = $scope.originalList;

  jQuery(document).on('volunteersLoaded', function () {
    $scope.filteredList = $scope.originalList = $window.valghalla_volunteers;

    $scope.$apply();
    // $scope.$evalAsync();
  });

  $scope.updateFilteredList = function () {
    $scope.filteredList = $filter('filter')($scope.originalList, $scope.query);
  };

  $scope.config = {
    itemsPerPage: 10,
    maxPages: 5,
    fillLastPage: "yes"
  };
}]);
